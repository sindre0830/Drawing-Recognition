package debug

import "net/http"

// Debug structure stores information about errors.
//
// Functionality: Update, Print
type Debug struct {
	StatusCode 		 int    `json:"status_code"`
	Location   		 string `json:"location"`
	RawError   		 string `json:"raw_error"`
	PossibleReason   string `json:"possible_reason"`
}

// Update sets new data in structure.
func (debug *Debug) Update(status int, loc string, err string, reason string) {
	debug.StatusCode = status
	debug.Location = loc
	debug.RawError = err
	//update reason if status code shows client error
	if status == http.StatusBadRequest || status == http.StatusNotFound || status == http.StatusMethodNotAllowed {
		debug.PossibleReason = reason
	} else {
		debug.PossibleReason = "Unknown"
	}
}
