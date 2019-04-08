#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>

class QQuickTextDocument;

class HighlightingRule {
public:
  HighlightingRule(const QString &patternStr, int n,
                   const QTextCharFormat &matchingFormat);
  QString originalRuleStr;
  QRegularExpression pattern;
  int nth;
  QTextCharFormat format;
};

class PythonSyntaxHighlighter : public QSyntaxHighlighter {
  Q_OBJECT
public:
  PythonSyntaxHighlighter(QTextDocument *parent);
  const QTextCharFormat getTextCharFormat(const QString &colorName,
                                          const QString &style = QString());
  void initializeRules();
  bool matchMultiline(const QString &text, const QRegularExpression &delimiter,
                      const int inState, const QTextCharFormat &style);

protected:
  void highlightBlock(const QString &text);

private:
  QStringList keywords;
  QStringList operators;
  QStringList braces;
  QHash<QString, QTextCharFormat> basicStyles;
  QList<HighlightingRule> rules;
  QRegularExpression triSingleQuote;
  QRegularExpression triDoubleQuote;
};

class SyntaxHighlighterHelper : public QObject {
  Q_OBJECT
  Q_PROPERTY(QQuickTextDocument *quickdocument READ quickdocument WRITE
                 setQuickdocument NOTIFY quickdocumentChanged)
public:
  SyntaxHighlighterHelper(QObject *parent = nullptr)
      : QObject(parent), m_quickdocument(nullptr) {}
  QQuickTextDocument *quickdocument() const;
  void setQuickdocument(QQuickTextDocument *quickdocument);
signals:
  void quickdocumentChanged();

private:
  QQuickTextDocument *m_quickdocument;
};

#endif // SYNTAXHIGHLIGHTER_H
