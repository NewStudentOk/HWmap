FROM ubuntu:latest
RUN apt-get update && apt-get install -y \
    clang \
    build-essential \
    && rm -rf /var/lib/apt/lists/*
WORKDIR  /app
COPY ./main.cpp .
RUN clang++ -o fig_side main.cpp 
CMD [ "./fig_side"]
