//
//  Foundation+SC.h
//  lunds
//
//  Created by kimberly on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


NSString * sc_docDirFilename(NSString *s);

BOOL sc_setResourceValue(NSString *filename, NSString *key, id value);

NSString* sc_JSONEncodedString(id x);


@interface NSObject ( SCKeyValueObserving )

-(void)addObserver: (NSObject *)o
       forKeyPaths: (NSArray *)ks;

-(void)removeObserver: (NSObject *)o
          forKeyPaths: (NSArray *)ks;

@end


@interface NSDictionary ( SlifterCore )

/**
 "{key1} text {key2}"  ->  self[key1] + " text " + self[key2]
 */
-(NSString *)stringWithFormat: (NSString *)f;

/**
 { 'a_b': 'x', 'a_c': 'y' }  ->  { 'a': { 'b': 'x', 'c': 'y' } }
 */
-(NSDictionary *)newNestedDictionaryWithKeySeparator: (NSString *)s;

/**
 Evaluates whether one dictionary matches all or part of another.
 
 Returns true if:
 
  * for every key k in d, d[k] == self[k]
 
 Example:
 
     NSDictionary *a=[NSDicitonary dictionaryWithObjectsAndKeys: @"1", @"x", nil];
     NSDictionary *b=[NSDictionary dictionaryWithObjectsAndKeys: @"2", @"y", nil];
     NSDictionary *c=[NSDictionary dictionaryWithObjectsAndKeys: @"1", @"x", @"1", @"y", nil];
 
     // Returns YES:  c[x] == a[x] == 1
     [c containsDictionary: a];
 
     // Returns NO:   c[y] == 1 but b[y] == 2
     [c containsDictionary: b];
 
     // Returns NO:   key 'y' exists in c but not in a
     [a containsDictionary: c];
 */
-(BOOL)containsDictionary: (NSDictionary *)d;

@end


@interface NSMutableDictionary ( SlifterCore )

-(void)scSafeSetObject: (id)o
                forKey: (id<NSCopying>)s;

@end


@interface NSMutableArray ( SlifterCore )

-(void)safeAddObject: (id)o;

@end


@interface NSString ( SlifterCore )

/**
 Ex. 1001 -> @"$ 10.01"
 
 @param c Dollar amount in cents.
 */
+(NSString *)newDollarStringFromCents: (uint64_t)c;

/**
 Formats a string of length 10 as (ccc) ccc-cccc
 */
-(NSString *)phoneFormattedString;

/**
 Replaces special placeholder substrings with properties from an object.
 
     @interface Employee
     @property (readonly) NSString *name;
     @property (readonly) NSString *title;
     @property (readonly) NSString *phone;
     @end
 
     Employee *john=[[Employee alloc] initWithName: @"John Doe" title: @"Developer" phone: nil];
     Employee *jane=[[Employee alloc] initWithName: @"Jane Doe" title: @"Client Services Representative" phone: @"1234567890"];
     NSString *s=@"<name> is a <title> and can be reached at '<phone>'.";
     NSArray *ps=[NSArray arrayWithObjects: @"name", @"title", @"phone", nil];
 
     // Returns @"John Doe is a Developer and can be reached at ''."
     [s stringByReplacingProperties: ps fromObject: john];
 
     // Returns @"Jane Doe is a Client Services Representative and can be reached at '1234567890'."
     [s stringByReplacingProperties: ps fromObject: jane];
 
     [john release];
     [jane release];
 
 @param ps The parameters to be replaced.
 
 @param i The source of the properties.  Every entry in ps should name a valid selector on i.
 */
-(NSString *)stringByReplacingProperties: (NSArray *)ps
                              fromObject: (id)i;
-(NSArray *)cookieValues;
-(NSString *)substringAfter: (NSString *)s;

+(BOOL)isValidEmail:(NSString *)s;
+(BOOL)isValidEmail:(NSString *)s useStrict:(BOOL)strictFilter;

/**
 @param s The character set against which to filter the string.
 
 @return The string formed by concatenating all the chars
 which are present in a given character set.
 */
-(NSString *)filteredStringConstrainedToCharacterSet: (NSCharacterSet *)s;

- (BOOL)isEqualToCaseInsensitiveString:(NSString *)aString;

@end



@interface NSBundle ( SlifterCore )

/**
 Checks the Main Bundle for a given key.
 
 @param key  Key for the Main Bundle Dictionary value.
 */
+ (id)mainBundleValueForKey:(NSString *)key;

/**
 Returns the ClientTypeId that is stored in the Main Bundle.  If this value does not exist, returns 0.
 */
+ (NSInteger)standardClientTypeId;

/**
 Returns the HostName that is stored in the Main Bundle.  If this value does not exist, returns nil.
 */
+ (NSString *)standardClientHostName;

/**
 Returns the Developer User Name.  This value, coupled with the standardDeveloperKey, is used to authenticate for the usage of certain GPS SDK features.  If this value does not exist, returns nil.
 */
+ (NSString *)standardDeveloperName;

/**
 Returns the Developer User Key.  This value, coupled with the standardDeveloperName, is used to authenticate for the usage of certain GPS SDK features.  If this value does not exist, returns nil.
 */
+ (NSString *)standardDeveloperKey;

/**
 Looks through the objects in a nib file and returns the first instance of a given class.
 
 @param f Name of the file to load.  .xib suffix not required.
 
 @param c Class to seek.  Subclasses are also considered matches.
 */
-(NSObject *)objectFromNibNamed: (NSString *)f
                        ofClass: (Class)c;

/**
 Returns the object for the specified key as an NSInteger.

 @param key Name of key from which to obtain value.
 */
- (NSInteger)intForInfoDictionaryKey:(NSString *)key;

@end


@interface NSDate ( SlifterCore )

/**
 Wraps strftime.  For use when NSDateFormatter will not return the format desired.
 
 @param f Date format
 */
-(NSString *)exactStringRepresentation: (char *)f;

@end
