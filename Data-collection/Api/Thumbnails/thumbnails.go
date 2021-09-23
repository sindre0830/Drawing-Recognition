package thumbnails

import (
	"fmt"
	debug "main/Debug"
	"net/http"
	"os"
	"path/filepath"
	"strings"
)

// Handler handles the request
func (thumbnails *Thumbnails) Handler(searchQuery string) {
	// Make sure every word in the query is separated by ONE space
	searchQuery = strings.Join(strings.Fields(searchQuery), " ")
	// All spaces needs to be replaced with "+" because of the Google Images API
	searchQuery = strings.ReplaceAll(searchQuery, " ", "+")

	// Fill the slice with image thumbnails
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
	}

	// Write result to a file
	status, err = thumbnails.WriteToFile(strings.ToLower(strings.ReplaceAll(searchQuery, "+", "_")))
	if err != nil {
		var errorMessage debug.Debug
		errorMessage.Update(
			status,
			"Thumbnails.Handler() -> Thumbnails.WriteToFile() -> Writing thumbnails to file",
			err.Error(),
			"Unknown",
		)
		errorMessage.Print()
	}
}

// get the thumbnails from the GoogleImages struct and add them to the thumbnails slice
func (thumbnails *Thumbnails) get(searchQuery string) (int, error) {
	var googleImages GoogleImages
	status, err := googleImages.get(searchQuery)

	for _, image := range googleImages.ImagesResults {
		*thumbnails = append(*thumbnails, image.Thumbnail)
	}

	return status, err
}

// WriteToFile writes all the image thumbnails to a file
func (thumbnails *Thumbnails) WriteToFile(name string) (int, error) {
	path := filepath.Join("data", name)

	// Create the data directory if it does not already exist
	if _, err := os.Stat("data"); os.IsNotExist(err) {
		err = os.MkdirAll("data", 0700)
		if err != nil {
			return http.StatusInternalServerError, err
		}
	}

	// Create and write to a new file if it does not already exist
	if _, err := os.Stat(path); os.IsNotExist(err) {
		file, err := os.Create(path)
		if err != nil {
			return http.StatusInternalServerError, err
		}
		defer file.Close()

		// Write every value to the file, each on a new line
		for _, val := range *thumbnails {
			_, err := fmt.Fprintln(file, val)
			if err != nil {
				return http.StatusInternalServerError, err
			}
		}
	}

	return http.StatusOK, nil
}