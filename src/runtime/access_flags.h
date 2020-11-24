//
// Created by tairy on 2020/11/24.
//

#ifndef TJVMSRC_ACCESS_FLAGS_H
#define TJVMSRC_ACCESS_FLAGS_H

#define ACC_PUBLIC              0x0001      // class field method
#define ACC_PRIVATE             0x0002      // class field method
#define ACC_PROTECTED           0x0004      // class field method
#define ACC_STATIC              0x0008      // class field method
#define ACC_FINAL               0x0010      // class field method
#define ACC_SUPER               0x0020      // class
#define ACC_SYNCHRONIZED        0x0020      // field
#define ACC_VOLATILE            0x0040      // field
#define ACC_BRIDGE              0x0040      // method
#define ACC_TRANSIENT           0x0080      // method
#define ACC_VARARGS             0x0080      // method
#define ACC_NATIVE              0x0100      // method
#define ACC_INTERFACE           0x0200      // class
#define ACC_ABSTRACT            0x0400      // class
#define ACC_STRICT              0x0800      // method
#define ACC_SYNTHETIC           0x1000      // class field method
#define ACC_ANNOTATION          0x2000      // class
#define ACC_ENUM                0x4000      // class field

#endif //TJVMSRC_ACCESS_FLAGS_H
