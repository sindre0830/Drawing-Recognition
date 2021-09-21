package thumbnails

import (
	debug2 "main/Debug"
	"net/http"
)

// MethodHandler handles the method of a http request
func MethodHandler(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		Handler(w, r)
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