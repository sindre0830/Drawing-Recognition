package dict

import "io/ioutil"

/* REST services */
var GOOGLEIMAGES_URL = "https://serpapi.com/search.json?engine=google"
var GOOGLEIMAGES_KEY string

// GetGoogleImagesURL generates google images REST service URL according to parameters.
func GetGoogleImagesURL(searchQuery string) string {
	return GOOGLEIMAGES_URL + "&q=" + searchQuery + "&google_domain=google.com&hl=en&tbm=isch&api_key=" + GOOGLEIMAGES_KEY
}

// GetGoogleImagesKey reads google images REST sevice key from file.
func GetGoogleImagesKey() (string, error) {
	// read file and branch if an error occurred
	key, err := ioutil.ReadFile("api-key")
	if err != nil {
		return "", err
	}
	return string(key), nil
}
