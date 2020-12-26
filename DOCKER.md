# Brayns Holography with Docker

> Use [Docker](https://docs.docker.com) to run Blue Brain BlackHole as a service and avoid painful tooling setup.


### Prerequisites
-----------------
Head over to [Docker](https://docs.docker.com/engine/installation/#supported-platforms) and install Docker for your own platform.


### Setup
---------
First build the image (*it's necessary to do this step if you want to run Brayns*):
```bash
docker build . -t holography
```


### Usage
---------
By default, the entrypoint when running the image is `braynsService`, but if you want to ssh into the container use:
```bash
# `-p 5000:5000` is used only to provide some port bindings (host:container) if you want to run and access Brayns from your host while in the container
docker run -ti --rm --entrypoint bash -p 5000:5000 holography
```

If you want to run Holography use:
```bash
# Runs Blue Brain BlackHole as a service with the HTTP interface binded on port 5000
docker run -ti --rm -p 5000:5000 holography
```

**NOTE** If you are having trouble exiting the process after you run the container (with the above command), use `docker stop <container-id>` to stop the container.
`docker ps` will give you the current running process.

If you'd like to also run the UI, use [docker stack](https://docs.docker.com/get-started/part5):
```bash
# UI on port 8000 and Python SDK on port 8888
docker stack deploy -c docker-compose.yml holography
```

**NOTE** You have to build both the UI and API images (using `docker-compose build`) before you can run them using stacks.

Run Holography with the HTTP interface binded to a different port:
```bash
docker run -ti --rm -p 5000:5000 holography --http-server :5000
```

Provide other flags (or env vars) to `braynsService`:
```bash
docker run -ti --rm -p 5000:5000 holography \
    --http-server :5000 \
    --plugin braynsHolography
```
