#ifndef DIFF_H
#define DIFF_H

#include <QtCore>

/**-
* The data structure representing a diff is a Linked list of Diff objects:
* {Diff(Operation.DELETE, "Hello"), Diff(Operation.INSERT, "Goodbye"),
*  Diff(Operation.EQUAL, " world.")}
* which means: delete "Hello", add "Goodbye" and keep " world."
*/
enum Operation {
  DELETE, INSERT, EQUAL
};


/**
* Class representing one diff operation.
*/
class Diff {
 public:
  Operation operation;
  // One of: INSERT, DELETE or EQUAL.
  QString text;
  // The text associated with this diff operation.

  /**
   * Constructor.  Initializes the diff with the provided values.
   * @param operation One of INSERT, DELETE or EQUAL.
   * @param text The text being applied.
   */
  Diff(Operation _operation, const QString &_text);
  Diff();
  inline bool isNull() const;
  QString toString() const;
  bool operator==(const Diff &d) const;
  bool operator!=(const Diff &d) const;

  static QString strOperation(Operation op);
};

#endif // DIFF_H
