package thumbnails

// GoogleImages stores image thumbnails.
type GoogleImages struct {
	ImagesResults []struct {
		Thumbnail string `json:"thumbnail"`
	} `json:"images_results"`
}

// Thumbnails stores image thumbnails in a cleaner format.
type Thumbnails []string
