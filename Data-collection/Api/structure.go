package Api

// Images stores image thumbnails
type Images struct {
	ImagesResults []struct {
		Thumbnail string `json:"thumbnail"`
	} `json:"images_results"`
}

