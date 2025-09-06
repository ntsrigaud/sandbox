# Holoscan-SDK

## Getting Started With the Holoscan SDK

Since we are using an **x86_64** workstation with a _dGPU_, using the **NGC container** is the simplest, easiest and recommended way of installing the SDK.

### Installing the NGC Container

We do so by pulling the NGC container:

```bash
docker pull nvcr.io/nvidia/clara-holoscan/holoscan:v3.6.0-dgpu
```

### Running the container

Start by logging into the NGC docker registry:

```bash
docker login nvcr.io
```

If successful, you will observe the following log output:

```console
Authenticating with existing credentials... [Username: $oauthtoken]

i Info → To login with a different account, run 'docker logout' followed by 'docker login'


Login Succeeded

```

#### Setting the container image path

If not already done, you might need to set a shell environment variable to locate the container image file as follows:

```bash
# For example
export NGC_CONTAINER_IMAGE_PATH="nvcr.io/nvidia/clara-holoscan/holoscan:v3.6.0-dgpu"
```

Then, you are finally ready to start the container using:

```bash
docker run -it --rm --net host \
  --runtime=nvidia \
  --ipc=host --cap-add=CAP_SYS_PTRACE --ulimit memlock=-1 --ulimit stack=67108864 \
  ${NGC_CONTAINER_IMAGE_PATH}
```

#### Leverage a Display

- **X11**
  - run `xhost +local:docker` as a prerequisite so that **X11** is configured to allow commands from docker
  - add `-v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY` to the `docker run` command

The updated command becomes:

```bash
docker run -it --rm --net host \
  --runtime=nvidia \
  --ipc=host \
  --cap-add=CAP_SYS_PTRACE \
  --ulimit memlock=-1 \
  --ulimit stack=67108864 \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -e DISPLAY \
  ${NGC_CONTAINER_IMAGE_PATH}
```

## Using the SDK

- Installation directory : `/opt/nvidia/holoscan`
- CMake configuration file: `lib/cmake/holoscan`

> [!IMPORTANT]
> To import **holoscan** in your CMake project (link libraries + headers), use the following CMake statements:

```CMake
find_package(holoscan REQUIRED CONFIG PATHS "/opt/nvidia/holoscan")
target_link_libraries(yourTarget PUBLIC holoscan::core)
```

[Additional CMake configuration information](https://cmake.org/cmake/help/v3.22/command/find_package.html#config-mode-search-procedure)

### Examples

Example applications are installed in `opt/nvidia/holoscan/examples` (also available on [GitHub](https://github.com/nvidia-holoscan/holoscan-sdk/tree/main/examples#readme)).

#### Building the examples

```bash
export src_dir="/opt/nvidia/holoscan/examples/" # Add "<example_of_your_choice>/cpp" to build a specific example
export build_dir="/opt/nvidia/holoscan/examples/build" # Or the path of your choice
cmake -S $src_dir -B $build_dir -D Holoscan_ROOT="/opt/nvidia/holoscan" -G Ninja
cmake --build $build_dir -j
```
