package thumbnails

import (
	debug2 "main/Debug"
	"net/http"
)

func MethodHandler(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		// Fetch data
	default:
		var debug debug2.Debug

		debug.Update(
			http.StatusMethodNotAllowed,
			"MethodHandler() -> Validating method",
			"validating method: wrong method",
			"Method not valid.",
			)

		debug.Print(w)
	}
}