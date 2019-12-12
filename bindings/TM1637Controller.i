%module TM1637ControllerBindings

%{
  #include "../src/TM1637_DotMatrixLEDController.h"
  #include "../src/TM1637_7SegmentLEDController.h"
  #include "../src/TM1637_OSL40391IXController.h"
%}

typedef unsigned char uint8_t;
typedef int int_fast32_t;
typedef unsigned int uint32_t;

%include "../src/WiringPi.h"

%csmethodmodifiers TM1637Controller::begin(const unsigned int) "[global::System.CLSCompliant(false)] public"
%csmethodmodifiers TM1637Controller::setDisplayBrightness(const unsigned int) "[global::System.CLSCompliant(false)] public"
%csmethodmodifiers TM1637Controller::getDisplayBrightness "[global::System.CLSCompliant(false)] public"
%include "../src/TM1637Controller.h"

%typemap(csclassmodifiers) TM1637_7SegmentLEDCustomSegmentAddressingController<1, 1, StandardSegmentAddressing> "public partial class"
%typemap(csclassmodifiers) TM1637_7SegmentLEDCustomSegmentAddressingController<2, 2, StandardSegmentAddressing> "public partial class"
%typemap(csclassmodifiers) TM1637_7SegmentLEDCustomSegmentAddressingController<3, 3, StandardSegmentAddressing> "public partial class"
%typemap(csclassmodifiers) TM1637_7SegmentLEDCustomSegmentAddressingController<4, 4, StandardSegmentAddressing> "public partial class"
%typemap(csclassmodifiers) TM1637_7SegmentLEDCustomSegmentAddressingController<5, 5, StandardSegmentAddressing> "public partial class"
%typemap(csclassmodifiers) TM1637_7SegmentLEDCustomSegmentAddressingController<6, 6, StandardSegmentAddressing> "public partial class"
%typemap(csattributes)     TM1637_7SegmentLEDCustomSegmentAddressingController<1, 1, StandardSegmentAddressing> "[global::System.CLSCompliant(false)]"
%typemap(csattributes)     TM1637_7SegmentLEDCustomSegmentAddressingController<2, 2, StandardSegmentAddressing> "[global::System.CLSCompliant(false)]"
%typemap(csattributes)     TM1637_7SegmentLEDCustomSegmentAddressingController<3, 3, StandardSegmentAddressing> "[global::System.CLSCompliant(false)]"
%typemap(csattributes)     TM1637_7SegmentLEDCustomSegmentAddressingController<4, 4, StandardSegmentAddressing> "[global::System.CLSCompliant(false)]"
%typemap(csattributes)     TM1637_7SegmentLEDCustomSegmentAddressingController<5, 5, StandardSegmentAddressing> "[global::System.CLSCompliant(false)]"
%typemap(csattributes)     TM1637_7SegmentLEDCustomSegmentAddressingController<6, 6, StandardSegmentAddressing> "[global::System.CLSCompliant(false)]"
%typemap(cstype) const char* const "global::System.IntPtr"
%typemap(imtype) const char* const "global::System.IntPtr"

%include "../src/TM1637_7SegmentLEDController.h"
%template(TM1637_1Digit7SegmentLEDController) TM1637_7SegmentLEDCustomSegmentAddressingController<1, 1, StandardSegmentAddressing>;
%template(TM1637_2Digit7SegmentLEDController) TM1637_7SegmentLEDCustomSegmentAddressingController<2, 2, StandardSegmentAddressing>;
%template(TM1637_3Digit7SegmentLEDController) TM1637_7SegmentLEDCustomSegmentAddressingController<3, 3, StandardSegmentAddressing>;
%template(TM1637_4Digit7SegmentLEDController) TM1637_7SegmentLEDCustomSegmentAddressingController<4, 4, StandardSegmentAddressing>;
%template(TM1637_5Digit7SegmentLEDController) TM1637_7SegmentLEDCustomSegmentAddressingController<5, 5, StandardSegmentAddressing>;
%template(TM1637_6Digit7SegmentLEDController) TM1637_7SegmentLEDCustomSegmentAddressingController<6, 6, StandardSegmentAddressing>;

%typemap(csclassmodifiers) TM1637_7SegmentLEDCustomSegmentAddressingController<4, 5, OSL40391IXStandardSegmentAddressing> "public partial class"
%typemap(csattributes)     TM1637_7SegmentLEDCustomSegmentAddressingController<4, 5, OSL40391IXStandardSegmentAddressing> "[global::System.CLSCompliant(false)]"
%typemap(csclassmodifiers) TM1637_OSL40391IXCustomSegmentAddressingController<OSL40391IXStandardSegmentAddressing> "public partial class"
%typemap(csattributes)     TM1637_OSL40391IXCustomSegmentAddressingController<OSL40391IXStandardSegmentAddressing> "[global::System.CLSCompliant(false)]"

%include "../src/TM1637_OSL40391IXController.h"
%template(TM1637_4Digit5Grid7SegmentLEDControllerBase) TM1637_7SegmentLEDCustomSegmentAddressingController<4, 5, OSL40391IXStandardSegmentAddressing>;
%template(TM1637_4Digit5Grid7SegmentLEDController) TM1637_4Digit5Grid7SegmentLEDCustomSegmentAddressingController<OSL40391IXStandardSegmentAddressing>;
%template(TM1637_OSL40391IXController) TM1637_OSL40391IXCustomSegmentAddressingController<OSL40391IXStandardSegmentAddressing>;

#if false
%include "../src/TM1637_DotMatrixLEDController.h"
%template(TM1637_8Cathodes6AnodesDotMatrixLEDController) TM1637_DotMatrixLEDController<8, 6>;
%template(TM1637_7Cathodes5AnodesDotMatrixLEDController) TM1637_DotMatrixLEDController<7, 5>;
%template(TM1637_4Cathodes4AnodesDotMatrixLEDController) TM1637_DotMatrixLEDController<4, 4>;
%template(TM1637_3Cathodes3AnodesDotMatrixLEDController) TM1637_DotMatrixLEDController<3, 3>;
%template(TM1637_2Cathodes2AnodesDotMatrixLEDController) TM1637_DotMatrixLEDController<2, 2>;
%template(TM1637_5Cathodes7AnodesDotMatrixLEDController) TM1637_DotMatrixLEDController<5, 7>;
%template(TM1637_6Cathodes8AnodesDotMatrixLEDController) TM1637_DotMatrixLEDController<6, 8>;

%template(TM1637_8CathodeColumns6AnodeRowsDotMatrixLEDController) TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<8, 6>;
%template(TM1637_7CathodeColumns5AnodeRowsDotMatrixLEDController) TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<7, 5>;
%template(TM1637_4CathodeColumns4AnodeRowsDotMatrixLEDController) TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<4, 4>;
%template(TM1637_3CathodeColumns3AnodeRowsDotMatrixLEDController) TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<3, 3>;
%template(TM1637_2CathodeColumns2AnodeRowsDotMatrixLEDController) TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<2, 2>;

%template(TM1637_6AnodeColumns8CathodeRowsDotMatrixLEDController) TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<6, 8>;
%template(TM1637_5AnodeColumns7CathodeRowsDotMatrixLEDController) TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<5, 7>;
%template(TM1637_4AnodeColumns4CathodeRowsDotMatrixLEDController) TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<4, 4>;
%template(TM1637_3AnodeColumns3CathodeRowsDotMatrixLEDController) TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<3, 3>;
%template(TM1637_2AnodeColumns2CathodeRowsDotMatrixLEDController) TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<2, 2>;
#endif