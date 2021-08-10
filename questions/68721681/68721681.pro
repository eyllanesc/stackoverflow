TEMPLATE = subdirs

SUBDIRS += \
    app \
    plugin

app.depends = plugin
