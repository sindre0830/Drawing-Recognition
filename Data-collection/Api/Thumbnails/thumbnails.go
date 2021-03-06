package thumbnails

import (
	"fmt"
	debug "main/Debug"
	"net/http"
	"os"
	"path/filepath"
	"strings"
)

// Handler handles the request.
func (thumbnails *Thumbnails) Handler(searchQuery string) string {
	// remove excess whitespace
	searchQuery = strings.Join(strings.Fields(searchQuery), " ")
	// make sure a search query is passed
	if !(len(searchQuery) > 0) {
		var errorMessage debug.Debug
		errorMessage.Update(
			http.StatusBadRequest,
			"Thumbnails.Handler() -> Check length of search query",
			"check length of searchQuery: The length is less than 0.",
			"A word has not been passed as a parameter",
		)
		errorMessage.Print()
		return ""
	}
	// all spaces needs to be replaced with "+" because of the way Google Images API handles multiple words
	searchQuery = strings.ReplaceAll(searchQuery, " ", "+")
	searchQuery = strings.ReplaceAll(searchQuery, "_", "+")
	fileName := strings.ToLower(strings.ReplaceAll(searchQuery, "+", "_")) + ".txt"
	path := filepath.Join("../Data/Thumbnails", fileName)
	// return the filename if the file already exists
	if _, err := os.Stat(path); err == nil {
		return fileName
	}
	// get thumbnails
	status, err := thumbnails.get(searchQuery)
	if err != nil {
		var errorMessage debug.Debug
		errorMessage.Update(
			status,
			"Thumbnails.Handler() -> Thumbnails.get() -> Get thumbnails from API",
			err.Error(),
			"Unknown",
		)
		errorMessage.Print()
		return ""
	}
	// write result to a file
	status, err = thumbnails.WriteToFile(path)
	if err != nil {
		var errorMessage debug.Debug
		errorMessage.Update(
			status,
			"Thumbnails.Handler() -> Thumbnails.WriteToFile() -> Writing thumbnails to file",
			err.Error(),
			"Unknown",
		)
		errorMessage.Print()
		return ""
	}
	return fileName
}

// get the thumbnails from the GoogleImages struct and add them to the thumbnails slice.
func (thumbnails *Thumbnails) get(searchQuery string) (int, error) {
	var googleImages GoogleImages
	status, err := googleImages.get(searchQuery)

	for _, image := range googleImages.ImagesResults {
		*thumbnails = append(*thumbnails, image.Thumbnail)
	}
	return status, err
}

// WriteToFile writes all the image thumbnails to a file.
func (thumbnails *Thumbnails) WriteToFile(path string) (int, error) {
	// create a data folder if it does not already exist
	if _, err := os.Stat("../Data/Thumbnails"); os.IsNotExist(err) {
		err = os.MkdirAll("../Data/Thumbnails", 0700)
		if err != nil {
			return http.StatusInternalServerError, err
		}
	}
	// create the file
	file, err := os.Create(path)
	if err != nil {
		return http.StatusInternalServerError, err
	}
	defer file.Close()
	// write every value to the file, each on a new line
	for _, val := range *thumbnails {
		_, err := fmt.Fprintln(file, val)
		if err != nil {
			return http.StatusInternalServerError, err
		}
	}
	return http.StatusOK, nil
}
