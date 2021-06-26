#include <QtCore/QDebug>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QRegExp>

#include <common.h>
#include <game_data/game_components.h>
#include <locale/string_table.h>

/**
 * @brief		Constructor.
 */
GameComponents::GameComponents(
    ::std::shared_ptr<GameVFS>             vfs,
    ::std::function<void(const QString &)> setTextFunc)
{
    setTextFunc(STR("STR_LOADING_COMPONENTS"));
    qDebug() << "Loading components...";

    // Open file.
    ::std::shared_ptr<GameVFS::FileReader> file
        = vfs->open("/index/components.xml");
    QByteArray       data = file->readAll();
    QXmlStreamReader reader(data);

    // Parse file
    /*
    auto context = XMLLoader::Context::create();
    context->setOnStartElement(
        ::std::bind(&GameComponents::onStartElementInRoot, this,
                    ::std::placeholders::_1, ::std::placeholders::_2,
                    ::std::placeholders::_3, ::std::placeholders::_4));
    XMLLoader loader;
    loader.parse(reader, ::std::move(context));
    */

    // Parse extension files
    ::std::shared_ptr<::GameVFS::DirReader> extensionsDir
        = vfs->openDir("/extensions");
    if (extensionsDir != nullptr) {
        for (auto iter = extensionsDir->begin(); iter != extensionsDir->end();
             ++iter) {
            if (iter->type == ::GameVFS::DirReader::EntryType::Directory) {
                file = vfs->open(QString("/extensions/%1/index/components.xml")
                                     .arg(iter->name));
                if (file == nullptr) {
                    continue;
                }
                data = file->readAll();
                QXmlStreamReader waresReader(data);

                /*
                // Parse ware file
                context = XMLLoader::Context::create();
                context->setOnStartElement(::std::bind(
                    &GameComponents::onStartElementInRoot, this,
                    ::std::placeholders::_1, ::std::placeholders::_2,
                    ::std::placeholders::_3, ::std::placeholders::_4));
                loader.parse(waresReader, ::std::move(context));
                */
            }
        }
    }

    this->setInitialized();
}

/**
 * @brief	Get component.
 */
QString GameComponents::component(const QString &id)
{
    return m_components[id];
}

/**
 * @brief		Destructor.
 */
GameComponents::~GameComponents() {}
