package Api

import (
	_ "main/Debug"
	"net/http"
)

func MethodHandler(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		// Fetch data
	default:
		// Error handling
	}

}