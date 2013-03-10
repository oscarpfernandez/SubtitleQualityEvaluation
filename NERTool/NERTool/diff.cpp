#include "diff.h"

/**
 * Constructor.  Initializes the diff with the provided values.
 * @param operation One of INSERT, DELETE or EQUAL
 * @param text The text being applied
 */
Diff::Diff(Operation _operation, const QString &_text) :
  operation(_operation), text(_text) {
  // Construct a diff with the specified operation and text.
}

Diff::Diff() {
}


QString Diff::strOperation(Operation op) {
  switch (op) {
    case INSERT:
      return "INSERT";
    case DELETE:
      return "DELETE";
    case EQUAL:
      return "EQUAL";
  }
  throw "Invalid operation.";
}

/**
 * Display a human-readable version of this Diff.
 * @return text version
 */
QString Diff::toString() const {
  QString prettyText = text;
  // Replace linebreaks with Pilcrow signs.
  prettyText.replace('\n', L'\u00b6');
  return QString("Diff(") + strOperation(operation) + QString(",\"")
      + prettyText + QString("\")");
}

/**
 * Is this Diff equivalent to another Diff?
 * @param d Another Diff to compare against
 * @return true or false
 */
bool Diff::operator==(const Diff &d) const {
  return (d.operation == this->operation) && (d.text == this->text);
}

bool Diff::operator!=(const Diff &d) const {
  return !(operator == (d));
}


