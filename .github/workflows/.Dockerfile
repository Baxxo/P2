FROM ubuntu:20.04
LABEL name="Qt"

# Set environment variables
ENV DEBIAN_FRONTEND noninteractive
ENV QT_VERSION_MAJOR 5.15
ENV QT_VERSION 5.15.2
ENV QT_DEST /usr/local/Qt-"$QT_VERSION"
ENV QT5BINDIR /usr/local/Qt-"$QT_VERSION"/bin
ENV LD_LIBRARY_PATH /usr/local/Qt-$QT_VERSION/lib
ENV QT_QPA_PLATFORM_PLUGIN_PATH /usr/lib/x86_64-linux-gnu/qt5/plugins/platforms
ENV QT_QPA_FONTDIR /usr/lib/x86_64-linux-gnu/qt5/lib/fonts
ENV XDG_DATA_HOME /root/.local/share
ENV PATH $QT_DEST/bin:$PATH

# Downlaod and install Qt
COPY qtlicenses.ini /root/.local/share/Qt/qtlicenses.ini
COPY getQt.sh /root/getQt.sh
CMD ["bash", "/root/getQt.sh"]
