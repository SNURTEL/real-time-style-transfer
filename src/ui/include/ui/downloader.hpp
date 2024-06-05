/**
 * @brief Module for managing downloading models
 */
#ifndef STYLE_APPLICATION_UI_DOWNLOADER_HPP
#define STYLE_APPLICATION_UI_DOWNLOADER_HPP

#include "common/model_manager.hpp"
#include <QObject>

class QThread;

/**
 * @brief Downloaded class
 */
class Downloader : public QObject {
  public:
    Downloader();

    /**
     * Download model
     * @param model Model to download
     */
    void download(modelManager::PretrainedModel model);

  private:
    std::shared_ptr<QThread> _thread;
};

#endif // STYLE_APPLICATION_UI_DOWNLOADER_HPP
