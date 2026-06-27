FROM nvcr.io/nvidia/pytorch:26.06-py3

# Set the working directory inside the container
WORKDIR /workspace

# Install JupyterLab and a visualization tools
RUN pip install --no-cache-dir jupyterlab matplotlib

# Expose the default Jupyter port inside the container
EXPOSE 8888

# Launch Jupyter Lab when the container starts
# --ip=0.0.0 allows connections from outside the container
# --allow-root is necessary since Docker containers run as root by default
# --NotebookApp.token='' and --NotebookApp.password='' disable authentication for simplicity (not recommended for production)
CMD ["jupyter", "lab", "--ip=0.0.0.0", "--port=8888", "--no-browser", "--allow-root", "--NotebookApp.token=''", "--NotebookApp.password=''"]
