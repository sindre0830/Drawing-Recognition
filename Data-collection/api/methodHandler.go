package api

import (
	"net/http"
)

func MethodHandler(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
		case http.MethodGet:
			// Add code for handling
		default:
			// TODO: error handling
			http.Error(w, "Not a valid method.", http.StatusMethodNotAllowed)
	}
}


