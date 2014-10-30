//
//  SCMacros.h
//  bestbuy
//
//  Created by kimberly on 1/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define DEF_STATIC_IMAGE_SETTER(funcName, varName) static UIImage *varName=nil; \
+(void)funcName: (UIImage *)im \
{ if (im != varName) \
{ [varName release]; varName=im; [varName retain]; } }


#define DEF_STATIC_LABEL_STYLE(funcName, varName) static LabelStyle *varName=nil; \
+(LabelStyle *)funcName \
{ if (!varName) \
{ varName=[[LabelStyle alloc] init]; [varName setFontSize: 14]; } \
return varName; }


#define DEF_STATIC_MUTABLE_STRING(setterFuncName, varName) static NSMutableString *varName=nil; \
+(void)setterFuncName: (NSString *)s\
{ if (!varName) { varName=[[NSMutableString alloc] init]; }\
[varName setString: s]; }

#define DEF_NULL_CHECK_GETTER(varType, getterFuncName, varName, errorMessage) \
+(varType *)getterFuncName { if (!varName) { NSLog(errorMessage); } return varName; }

#define DEF_STATIC_MUTABLE_STRING_GETSET(uncappedVarName, cappedVarName, className) \
static NSMutableString *className ## cappedVarName=nil; \
+(void)set ## cappedVarName: (NSString *)s\
{ if (!className ## cappedVarName) { className ## cappedVarName=[[NSMutableString alloc] init]; }\
    [className ## cappedVarName setString: s]; } \
+(NSString *)uncappedVarName \
{ if (!className ## cappedVarName) \
{ NSLog(@"ERROR:  %s has nil %s.  Call [%s set%s:] during startup config.", #className, #uncappedVarName, #className, #cappedVarName); } \
return className ## cappedVarName; }

#define DECODE_UINT64_TO_VAR(coderName, varName) \
NSNumber *n_ ## varName = [coderName decodeObjectForKey: @#varName]; \
varName=(n_ ## varName ? [n_ ## varName unsignedLongLongValue] : 0);

#define ENCODE_VAR_AS_UINT64(coderName, varName) \
NSNumber *n_ ## varName=[[NSNumber alloc] initWithUnsignedLongLong: varName]; \
[coderName encodeObject: n_ ## varName forKey: @#varName]; \
[n_ ## varName release];

#define DECODE_NSOBJECT_TO_VAR(coderName, varName) \
varName=[coderName decodeObjectForKey: @#varName]; \
[varName retain];

#define ENCODE_VAR_AS_NSOBJECT(coderName, varName) \
if (varName) { [coderName encodeObject: varName forKey: @#varName]; }

#define DEF_STATIC_COLOR_GETTER(getterName, varName, r, g, b, a) \
+(UIColor *)getterName \
{ if (!varName) { varName=[[UIColor alloc] initWithRed: r green: g blue: b alpha: a]; }  return varName; }

#define DEF_STATIC_OBJ_SETTER(setterName, varName, class) \
+(void)setterName: (class *)x \
{ if (x != varName) { [varName release]; varName=x; [varName retain]; } }

#define RELEASE_ASSIGN_RETAIN(leftVar, rightVar) \
if (rightVar != leftVar) \
{ [leftVar release]; leftVar=rightVar; [leftVar retain]; }

#define RELEASE_ASSIGN_RETAIN_THEN(leftVar, rightVar, postAction) \
if (rightVar != leftVar) \
{ [leftVar release]; leftVar=rightVar; [leftVar retain]; postAction }

#define RELEASE_ASSIGN_RETAIN_LISTEN(leftVar, rightVar, notificationName, selectorName) \
if (rightVar != leftVar) \
{ [[NSNotificationCenter defaultCenter] removeObserver: self name: notificationName object: nil]; \
  [leftVar release]; leftVar=rightVar; [leftVar retain]; \
  if (leftVar) { [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(selectorName) name: notificationName object: leftVar]; } }

#define RELEASE_ASSIGN_RETAIN_OBSERVE(leftVar, rightVar, keyPath) \
if (leftVar != rightVar) \
{ \
[leftVar removeObserver: self forKeyPath: keyPath]; \
[leftVar release]; leftVar=rightVar; [leftVar retain]; \
[leftVar addObserver: self forKeyPath: keyPath options: 0 context: NULL]; \
}

#define DO_ON_MAIN_THREAD(selectorName) \
if (![[NSThread currentThread] isMainThread]) \
{ [self performSelectorOnMainThread: @selector(selectorName) withObject: nil waitUntilDone: NO]; return; }

#define DO_ON_MAIN_THREAD_ARGS(selName, obj, wt) \
if (![[NSThread currentThread] isMainThread]) \
{ [self performSelectorOnMainThread: @selector(selName) withObject: obj waitUntilDone: wt]; return; }


#define FORWARD_SELECTOR(var, sel, rettype, defval) \
-(rettype)sel { return (var ? [var sel] : defval); }

#define ASSIGN_THEN(leftVar, rightVar, postAction) \
if (rightVar != leftVar) { leftVar=rightVar; postAction }

#define COPY_STR_THEN(leftVar, rightVar, postAction) \
if ((leftVar && ![leftVar isEqualToString: rightVar]) \
|| (rightVar && ![rightVar isEqualToString: leftVar])) \
{ [leftVar release]; leftVar=[rightVar copy]; postAction }

#define RELEASE_NIL(var) \
[var release];  var=nil; 

#define KVO_SET_VAR(var, value, key) \
if (var != value) \
{ [self willChangeValueForKey: key]; var=value; [self didChangeValueForKey: key]; }
