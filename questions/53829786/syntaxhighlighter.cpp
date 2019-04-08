#include "syntaxhighlighter.h"
#include <QQuickTextDocument>

HighlightingRule::HighlightingRule(const QString &patternStr, int n,
                                   const QTextCharFormat &matchingFormat) {
  originalRuleStr = patternStr;
  pattern = QRegularExpression(patternStr);
  nth = n;
  format = matchingFormat;
}

PythonSyntaxHighlighter::PythonSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
  keywords = QStringList() << "and"
                           << "assert"
                           << "break"
                           << "class"
                           << "continue"
                           << "def"
                           << "del"
                           << "elif"
                           << "else"
                           << "except"
                           << "exec"
                           << "finally"
                           << "for"
                           << "from"
                           << "global"
                           << "if"
                           << "import"
                           << "in"
                           << "is"
                           << "lambda"
                           << "not"
                           << "or"
                           << "pass"
                           << "print"
                           << "raise"
                           << "return"
                           << "try"
                           << "while"
                           << "yield"
                           << "None"
                           << "True"
                           << "False";

  operators = QStringList() << "=" <<
              // Comparison
              "=="
                            << "!="
                            << "<"
                            << "<="
                            << ">"
                            << ">=" <<
              // Arithmetic
              "\\+"
                            << "-"
                            << "\\*"
                            << "/"
                            << "//"
                            << "%"
                            << "\\*\\*" <<
              // In-place
              "\\+="
                            << "-="
                            << "\\*="
                            << "/="
                            << "%=" <<
              // Bitwise
              "\\^"
                            << "\\|"
                            << "&"
                            << "~"
                            << ">>"
                            << "<<";

  braces = QStringList() << "{"
                         << "}"
                         << "\\("
                         << "\\)"
                         << "\\["
                         << "]";

  basicStyles.insert("keyword", getTextCharFormat("blue"));
  basicStyles.insert("operator", getTextCharFormat("red"));
  basicStyles.insert("brace", getTextCharFormat("darkGray"));
  basicStyles.insert("defclass", getTextCharFormat("black", "bold"));
  basicStyles.insert("brace", getTextCharFormat("darkGray"));
  basicStyles.insert("string", getTextCharFormat("magenta"));
  basicStyles.insert("string2", getTextCharFormat("darkMagenta"));
  basicStyles.insert("comment", getTextCharFormat("darkGreen", "italic"));
  basicStyles.insert("self", getTextCharFormat("black", "italic"));
  basicStyles.insert("numbers", getTextCharFormat("brown"));

  triSingleQuote.setPattern("'''");
  triDoubleQuote.setPattern("\"\"\"");

  initializeRules();
}

void PythonSyntaxHighlighter::initializeRules() {
  for (const QString &currKeyword : keywords) {
    rules.append(HighlightingRule(QString("\\b%1\\b").arg(currKeyword), 0,
                                  basicStyles.value("keyword")));
  }
  for (const QString &currOperator : operators) {
    rules.append(HighlightingRule(QString("%1").arg(currOperator), 0,
                                  basicStyles.value("operator")));
  }
  for (const QString &currBrace : braces) {
    rules.append(HighlightingRule(QString("%1").arg(currBrace), 0,
                                  basicStyles.value("brace")));
  }
  // 'self'
  rules.append(HighlightingRule("\\bself\\b", 0, basicStyles.value("self")));

  // Double-quoted string, possibly containing escape sequences
  // FF: originally in python : r'"[^"\\]*(\\.[^"\\]*)*"'
  rules.append(HighlightingRule("\"[^\"\\\\]*(\\\\.[^\"\\\\]*)*\"", 0,
                                basicStyles.value("string")));
  // Single-quoted string, possibly containing escape sequences
  // FF: originally in python : r"'[^'\\]*(\\.[^'\\]*)*'"
  rules.append(HighlightingRule("'[^'\\\\]*(\\\\.[^'\\\\]*)*'", 0,
                                basicStyles.value("string")));

  // 'def' followed by an identifier
  // FF: originally: r'\bdef\b\s*(\w+)'
  rules.append(HighlightingRule("\\bdef\\b\\s*(\\w+)", 1,
                                basicStyles.value("defclass")));
  //  'class' followed by an identifier
  // FF: originally: r'\bclass\b\s*(\w+)'
  rules.append(HighlightingRule("\\bclass\\b\\s*(\\w+)", 1,
                                basicStyles.value("defclass")));

  // From '#' until a newline
  // FF: originally: r'#[^\\n]*'
  rules.append(HighlightingRule("#[^\\n]*", 0, basicStyles.value("comment")));

  // Numeric literals
  rules.append(HighlightingRule(
      "\\b[+-]?[0-9]+[lL]?\\b", 0,
      basicStyles.value("numbers"))); // r'\b[+-]?[0-9]+[lL]?\b'
  rules.append(HighlightingRule(
      "\\b[+-]?0[xX][0-9A-Fa-f]+[lL]?\\b", 0,
      basicStyles.value("numbers"))); // r'\b[+-]?0[xX][0-9A-Fa-f]+[lL]?\b'
  rules.append(HighlightingRule(
      "\\b[+-]?[0-9]+(?:\\.[0-9]+)?(?:[eE][+-]?[0-9]+)?\\b", 0,
      basicStyles.value(
          "numbers"))); // r'\b[+-]?[0-9]+(?:\.[0-9]+)?(?:[eE][+-]?[0-9]+)?\b'
}

void PythonSyntaxHighlighter::highlightBlock(const QString &text) {
  for (const HighlightingRule &rule : rules) {
    QRegularExpressionMatchIterator matchIterator =
        rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
      QRegularExpressionMatch match = matchIterator.next();
      setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
  }
  setCurrentBlockState(0);
  bool isInMultilne =
      matchMultiline(text, triSingleQuote, 1, basicStyles.value("string2"));
  if (!isInMultilne)
    isInMultilne =
        matchMultiline(text, triDoubleQuote, 2, basicStyles.value("string2"));
}

bool PythonSyntaxHighlighter::matchMultiline(
    const QString &text, const QRegularExpression &delimiter, const int inState,
    const QTextCharFormat &style) {
  QRegularExpressionMatch match;
  int startIndex = 0;
  if (previousBlockState() != 1)
    startIndex = text.indexOf(delimiter);
  while (startIndex >= 0) {
    QRegularExpressionMatch match = delimiter.match(text, startIndex);
    int endIndex = match.capturedStart();
    int commentLength = 0;
    if (endIndex == -1) {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    } else {
      commentLength = endIndex - startIndex + match.capturedLength();
    }
    setFormat(startIndex, commentLength, style);
    startIndex = text.indexOf(delimiter, startIndex + commentLength);
  }

  return currentBlockState() == inState;
}

const QTextCharFormat
PythonSyntaxHighlighter::getTextCharFormat(const QString &colorName,
                                           const QString &style) {
  QTextCharFormat charFormat;
  QColor color(colorName);
  charFormat.setForeground(color);
  if (style.contains("bold", Qt::CaseInsensitive))
    charFormat.setFontWeight(QFont::Bold);
  if (style.contains("italic", Qt::CaseInsensitive))
    charFormat.setFontItalic(true);
  return charFormat;
}

QQuickTextDocument *SyntaxHighlighterHelper::quickdocument() const {
  return m_quickdocument;
}

void SyntaxHighlighterHelper::setQuickdocument(
    QQuickTextDocument *quickdocument) {
  m_quickdocument = quickdocument;
  if (m_quickdocument) {
    new PythonSyntaxHighlighter(m_quickdocument->textDocument());
  }
}
