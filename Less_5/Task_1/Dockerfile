FROM ubuntu:24.04
RUN apt update && apt install -y g++ mc
WORKDIR  /app
COPY ./src/main.cpp .
RUN g++ main.cpp -o h_w
CMD [ "./h_w"]
