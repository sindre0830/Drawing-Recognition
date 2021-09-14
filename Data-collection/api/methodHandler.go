package api

import (
	"fmt"
	"net/http"
)

func MethodHandler(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
		case http.MethodGet:
			fmt.Println("heihei")
		default:
			// TODO: error handling
			http.Error(w, "Not a valid method.", http.StatusMethodNotAllowed)
	}
}


