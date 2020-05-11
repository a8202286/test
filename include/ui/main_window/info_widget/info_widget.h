#pragma once

#include <ui/main_window/action_control_dock_widget.h>

class InfoWidget : public ActionControlDockWidget {
    Q_OBJECT

  public:
    /**
     * @brief		Constructor.
     *
     * @param[in]	statusAction	Action to control the visibility of the
     *								widget.
     * @param[in]	parent			Parent object.
     * @param[in]	flags			Window flags.
     */
    InfoWidget(QAction *       statusAction,
               QWidget *       parent = nullptr,
               Qt::WindowFlags flags  = Qt::WindowFlags());

    /**
     * @brief		Destructor.
     */
    virtual ~InfoWidget();

  public slots:
    /**
     * @brief		Change language.
     */
    void onLanguageChanged();
};
