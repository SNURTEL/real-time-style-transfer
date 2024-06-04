#include <QThread>

#include "ui/downloader.hpp"
#include "common/model_manager.hpp"

Downloader::Downloader() : QObject() {
    _thread = std::make_shared<QThread>();
    moveToThread(_thread.get());
}

void Downloader::download(modelManager::PretrainedModel model) {
    modelManager::getOrDownloadModelPath(model);
}