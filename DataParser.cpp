#include "DataParser.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

#include <string_view>

namespace
{
    constexpr std::string_view fileName {":/data.json"};
}

QStringList Utils::Parser::parse()
{
    QFile file(fileName.data());

    QStringList names;

    // TODO: make throw or close app
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "No such file or directory";
        return {};
    }

    QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
    const QJsonArray namesArray = obj.value("names").toArray();

    for (const auto& name : namesArray)
        names.push_back(name.toString());

    return names;
}
