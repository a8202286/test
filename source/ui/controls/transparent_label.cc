#include <QtCore/QFile>
#include <QtCore/QtDebug>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtWidgets/QStyleOption>

#include <ui/controls/transparent_label.h>

/**
 * @brief       Constructor.
 */
TransparentLabel::TransparentLabel(const QString &text, QWidget *parent) :
    QLabel(text, parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    // Set style sheet
    this->setProperty("class", "TransparentLabel");
    this->setAlignment(Qt::AlignmentFlag::AlignLeft
                       | Qt::AlignmentFlag::AlignTop);

    this->setWordWrap(true);
    this->adjustSize();
}

/**
 * @brief       Constructor.
 */
TransparentLabel::TransparentLabel(QWidget *parent) : QLabel(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    // Set style sheet
    this->setProperty("class", "TransparentLabel");
    this->setAlignment(Qt::AlignmentFlag::AlignLeft
                       | Qt::AlignmentFlag::AlignTop);

    this->setWordWrap(true);
    this->adjustSize();
}

/**
 * @brief       Destructor.
 */
TransparentLabel::~TransparentLabel() {}
