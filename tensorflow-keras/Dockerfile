FROM nvcr.io/nvidia/tensorflow:25.02-tf2-py3

# Set the working directory inside the container
WORKDIR /workspace

# Install JupyterLab and visualization tools
RUN pip install --no-cache-dire jupyterlab matplotlib

# Expose the default Jupyter port inside the container
EXPOSE 8888

# Launch Jupyter Lab when the container starts
CMD ["jupyter", "lab", "--ip=0.0.0.0", "--port=8888", "--no-browser", "--allow-root", "--NotebookApp.token=''", "--NotebookApp.password=''"]
