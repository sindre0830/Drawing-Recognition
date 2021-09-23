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

	fmt.Println(searchQuery)

	*thumbnails = []string{"test 1", "test 2", "test 3", "test 4"}
	/*err := thumbnails.get(searchQuery)
	if err != nil {
		// Handle error
	}*/

	// Write result to a file
	err := thumbnails.WriteToFile(strings.ToLower(strings.ReplaceAll(searchQuery, "+", "_")))
	if err != nil {
		var debug debug.Debug
		debug.Update(
			http.StatusInternalServerError,
			"Handler() -> WriteToFile() -> Writing thumbnails to file",
			err.Error(),
			"Unknown",
		)
		debug.Print()
	}
}



// WriteToFile writes all the image thumbnails to a file
func (thumbnails Thumbnails) WriteToFile(name string) error {
	path := filepath.Join("data", name)

	// Create the data directory if it does not already exist
	if _, err := os.Stat("data"); os.IsNotExist(err) {
		os.MkdirAll("data", 0700)
	}

	// Create and write to a new file if it does not already exist
	if _, err := os.Stat(path); os.IsNotExist(err) {
		file, err := os.Create(path)
		if err != nil {
			return err
		}
		defer file.Close()

		// Write every value to the file, each on a new line
		for _, val := range thumbnails {
			fmt.Fprintln(file, val)
		}
	}

	return nil
}