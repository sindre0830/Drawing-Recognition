package thumbnails

import (
	"encoding/json"
	api "main/Api"
	"net/http"
)

func (googleImages *GoogleImages) req(url string) (int, error) {
	//gets raw data from API and branch if an error occurred
	output, status, err := api.RequestData(url)
	if err != nil {
		return status, err
	}
	//convert raw data to JSON and branch if an error occurred
	err = json.Unmarshal(output, &googleImages)
	if err != nil {
		return http.StatusInternalServerError, err
	}
	return http.StatusOK, nil
}
