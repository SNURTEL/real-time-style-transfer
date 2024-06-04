#include <QThread>

#include "ui/downloader.hpp"
#include "common/model_manager.hpp"

Downloader::Downloader() {
    _thread = std::make_shared<QThread>();
    moveToThread(_thread.get());
}

void Downloader::download(modelManager::PretrainedModel model) {
    modelManager::getOrDownloadModelPath(model);
    emit downloadComplete();
}

#include "downloader.moc"