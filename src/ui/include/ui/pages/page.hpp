#ifndef STYLE_APPLICATION_UI_PAGES_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_PAGE_HPP

#include <QWidget>

class State;

/**
 * @brief Base Page class
 */
class Page : public QWidget {
public:
    explicit Page(QWidget *parent, std::shared_ptr<State> state);

    /**
     * @brief Activates page
     */
    virtual void activatePage();

    /**
     * @brief Deactivates page
     */
    virtual void deactivatePage();

    /**
     * @brief Checking if page is active
     * @return true if page is active, false otherwise
     */
    virtual bool isActive();

private:
    bool _active{false};
protected:
    std::shared_ptr<State> _state;
};

#endif //STYLE_APPLICATION_UI_PAGES_PAGE_HPP
