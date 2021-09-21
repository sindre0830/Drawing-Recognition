package thumbnails

import (
	"fmt"
	debug2 "main/Debug"
	"net/http"
	"os"
	"strings"
)

// Handler handle the http request
func Handler(w http.ResponseWriter, r *http.Request) {
	// Parse URL to retrieve path parameters
	path := strings.Split(r.URL.Path, "/")

	// TODO: check if length of path is correct

	word := path[1]

	var thumbnails Thumbnails

	// TODO: replace this with actual data
	thumbnails = make([]string, 4)
	thumbnails = []string{"test 1", "test 2", "test 3", "test 4"}

	// Write result to a file
	err := thumbnails.WriteToFile(strings.ToLower(word))
	if err != nil {
		var debug debug2.Debug
		debug.Update(
			http.StatusInternalServerError,
			"Handler() -> WriteToFile() -> Writing thumbnails to file",
			err.Error(),
			"Unknown",
		)
		debug.Print(w)
	}
}

// WriteToFile writes all the image thumbnails to a file
func (thumbnails Thumbnails) WriteToFile(name string) error {
	file, err := os.Create("./data/" + name + ".txt")
	if err != nil {
		return err
	}
	defer file.Close()

	// Write every value to the file, each on a new line
	for _, val := range thumbnails {
		fmt.Fprintln(file, val)
	}

	return nil
}