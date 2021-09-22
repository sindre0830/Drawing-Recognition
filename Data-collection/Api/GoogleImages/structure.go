package googleImages

// GoogleImages stores image thumbnails
type GoogleImages struct {
	ImagesResults []struct {
		Thumbnail string `json:"thumbnail"`
	} `json:"images_results"`
}
