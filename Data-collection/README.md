# Data Collection API

This server runs the API that handles data retrieving and data transmission. It will take a query and send it to SerpAPI and retreive a list of URLs to the thumbnails in Google Images.

It requires a SerpAPI account where (as of 2021-12-05) you get 100 free request per month. You need to make an api-key.txt file and add your api key inside there to be able to request.

## Installation guide

```sh
# Install dependencies
sudo apt-get install libzmq3-dev
# Build
go build -v ./main.go
# Run
./main
# CTRL-C to terminate server
```
