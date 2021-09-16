package Api

type Images struct {
	ImagesResults []struct {
		Thumbnail string `json:"thumbnail"`
	} `json:"images_results"`
}

