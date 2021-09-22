package dict

import "io/ioutil"

/* REST services */
var GOOGLEIMAGES_URL = "https://serpapi.com/search.json?engine=google"
var GOOGLEIMAGES_KEY = ""

func GetGoogleImagesURL(searchQuery string) string {
	return GOOGLEIMAGES_URL + "&q=" + searchQuery + "&google_domain=google.com&hl=en&tbm=isch&api_key=" + GOOGLEIMAGES_KEY
}

func GetGoogleImagesKey() (string, error) {
	key, err := ioutil.ReadFile("api-key.txt")
	if err != nil {
		return "", err
	}
	return string(key), nil
}
