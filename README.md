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

- Run the output binary in a Debian container.

```bash
docker pull debian:10.1
docker run --rm -v ${PWD}/bin:/dev/test -w /dev/test debian:10.1 ./wscrap [OPTIONS]
```
