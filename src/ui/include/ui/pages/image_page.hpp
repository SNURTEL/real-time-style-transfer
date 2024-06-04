#ifndef STYLE_APPLICATION_UI_PAGES_IMAGE_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_IMAGE_PAGE_HPP

#include <QWidget>

#include "page.hpp"

class QVBoxLayout;

class QHBoxLayout;

class QLabel;

class QPushButton;

class State;

/**
 * @brief Image inference page
 */
class ImagePage : public Page {
public:
    explicit ImagePage(QWidget *parent, std::shared_ptr<State> state);

    /**
     * @brief Setups UI for Image Page
     */
    void setupUi();

    /**
     * @brief Updates UI for Image Page
     */
    void updateUi();

    /**
     * @brief Activates page
     */
    void activatePage() override;

    /**
     * @brief Deactivates page
     */
    void deactivatePage() override;

private slots:

    void onLoadImageButtonClicked();

    void onTransformButtonClicked();

private:
    std::shared_ptr<QVBoxLayout> _layout;
    std::shared_ptr<QHBoxLayout> _imagesLayout;
    std::shared_ptr<QHBoxLayout> _controlsLayout;
    std::shared_ptr<QLabel> _title;
    std::shared_ptr<QLabel> _inputImage;
    std::shared_ptr<QLabel> _outputImage;
    std::shared_ptr<QPushButton> _loadImageButton;
    std::shared_ptr<QPushButton> _transformButton;
    std::optional<std::string> _inputImagePath;
};


#endif //STYLE_APPLICATION_UI_PAGES_IMAGE_PAGE_HPP
