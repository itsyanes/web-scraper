# Web Scraper

## Description

This is a Command Line application used to extract data from any given website.

## Installation

- Install Docker.

- Open a Prompt.

- Navigate to project folder.

- Install gcc 9.2 image and build the sources.

```bash
docker pull gcc:9.2
docker run --rm -v ${PWD}:/dev/test -w  /dev/test gcc:9.2 make all
```

- Build the image used to run the app.

```bash
docker build -t dev-env --force-rm .
```

- Run the output binary in a container.

```bash
// Linux
docker run --rm -v ${PWD}/bin:/dev/test dev-env ./wscrap
// Windows
docker run --rm -v ${PWD}/bin:/dev/test -e PWD=/dev/test dev-env ./wscrap
```

## Documentation

Check the project documentation [here](https://theghostspirit.github.io/web-scraper/).
