//
//  SCBaseProduct.h
//  schumacher
//
//  Created by kimberly on 7/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SCMacros.h"


//----------------------------------------------------------------
//----------------------------------------------------------------


@protocol SCBaseProduct < NSObject >

-(uint64_t)grpid;

/**
 @warning DEPRECATED.  Use 'parent' instead.
 */
-(uint64_t)parentGrpid;
-(id<SCBaseProduct>)parent;
-(NSString *)productName;
-(NSString *)sku;
-(NSString *)retailerProductID;
-(NSString *)shortDescription;
-(NSString *)longDescription; 
-(NSString *)immediateProductName;
-(NSString *)immediateSku;
-(NSString *)immediateShortDescription;
-(NSString *)immediateLongDescription;

-(NSDictionary *)supplemental;
-(NSArray *)newSupplementalKeysWithPrefix: (NSString *)s
                            startingIndex: (int)i;
-(NSArray *)newSupplementalValuesWithPrefix: (NSString *)s
                              startingIndex: (int)i;
-(NSString *)urlForImageWithinSize: (CGSize)s factor: (CGFloat)factor;
-(NSString *)urlForImageWithinSize: (CGSize)s;
-(NSDictionary *)images;

@end


@protocol SCBaseProductArrayFunction < NSObject >
-(NSArray *)arrayFromBaseProduct: (id<SCBaseProduct>)p;
@end

#define SCBASEPRODUCT_SUP_FN(funcName, key, defval) \
-(NSString *)funcName \
{ NSString *supVal=[supplemental objectForKey: key]; \
  return (supVal ? supVal : defval); }


@interface NSString ( SCBaseProduct )

-(NSString *)stringByReplacingPropertiesFromBaseProduct: (id<SCBaseProduct>)p;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface SCBaseProduct : NSObject < NSCoding, SCBaseProduct >
{
    uint64_t grpid;
    uint64_t parentGrpid;
    NSString *productName;
	NSString *manufacturer;
	NSString *brand;
	NSString *sku;
	NSString *upc;
	NSString *mpn;
    NSString *retailerProductID;
	NSString *shortDescription;
	NSString *longDescription;
    NSDictionary *supplemental;
    NSDictionary *images;
    SCBaseProduct *parent;
}

@property (readonly) NSString *manufacturer;
@property (readonly) NSString *brand;
@property (readonly) NSString *upc;
@property (readonly) NSString *mpn;
@property (readonly) NSString *retailerProductID;
@property (readonly) NSDictionary *supplemental;
@property (readonly) NSDictionary *images;
@property (readonly) SCBaseProduct *parent;

-(id)initWithGrpid: (uint64_t)g
              name: (NSString *)n
      manufacturer: (NSString *)m0
             brand: (NSString *)b
               sku: (NSString *)s0
               upc: (NSString *)u
               mpn: (NSString *)m1
 retailerProductID: (NSString *)r
  shortDescription: (NSString *)s1
   longDescription: (NSString *)l
      supplemental: (NSDictionary *)s2
            images: (NSDictionary *)is
            parent: (SCBaseProduct *)p;

/**
 @warning  DEPRECATED.  Use constructor with 'rpid' arg instead.
 */
-(id)initWithGrpid: (uint64_t)g
              name: (NSString *)n
      manufacturer: (NSString *)m0
             brand: (NSString *)b
               sku: (NSString *)s0
               upc: (NSString *)u
               mpn: (NSString *)m1
  shortDescription: (NSString *)s1
   longDescription: (NSString *)l
      supplemental: (NSDictionary *)s2
            images: (NSDictionary *)is
            parent: (SCBaseProduct *)p;

/**
 @warning  DEPRECATED.  Use constructor with 'parent' arg instead.
 */
-(id)initWithGrpid: (uint64_t)g
       parentGrpid: (uint64_t)p
              name: (NSString *)n
      manufacturer: (NSString *)m0
             brand: (NSString *)b
               sku: (NSString *)s0
               upc: (NSString *)u
               mpn: (NSString *)m1
  shortDescription: (NSString *)s1
   longDescription: (NSString *)l
      supplemental: (NSDictionary *)s2
            images: (NSDictionary *)is;


-(id)initWithProduct: (SCBaseProduct *)p;

-(void)updateWithDictionary: (NSDictionary *)d;

-(NSDictionary *)newDictionary;

+(SCBaseProduct *)newFromDictionary: (NSDictionary *)d;

+(NSArray *)allProductFields;

+(NSArray *)supplementalValuesForProducts: (NSArray *)ps
                                      key: (NSString *)k;

@end

#define FORWARD_SCBASEPRODUCT_IMPL(var) \
FORWARD_SELECTOR(var, grpid, uint64_t, 0) \
FORWARD_SELECTOR(var, parentGrpid, uint64_t, 0) \
FORWARD_SELECTOR(var, productName, NSString *, nil) \
FORWARD_SELECTOR(var, sku, NSString *, nil) \
FORWARD_SELECTOR(var, upc, NSString *, nil) \
FORWARD_SELECTOR(var, retailerProductID, NSString *, nil) \
FORWARD_SELECTOR(var, shortDescription, NSString *, nil) \
FORWARD_SELECTOR(var, longDescription, NSString *, nil) \
FORWARD_SELECTOR(var, supplemental, NSDictionary *, nil) \
FORWARD_SELECTOR(var, images, NSDictionary *, nil) \
FORWARD_SELECTOR(var, imageUrl, NSString *, nil) \
-(NSString *)urlForImageWithinSize: (CGSize)s factor: (CGFloat)factor \
{ return (var ? [var urlForImageWithinSize: s factor: factor] : nil); } \
-(NSString *)urlForImageWithinSize: (CGSize)s \
{ return (var ? [var urlForImageWithinSize: s] : nil); } \
FORWARD_SELECTOR(var, parent, id<SCBaseProduct>, nil) \
-(NSArray *)newSupplementalKeysWithPrefix: (NSString *)s startingIndex: (int)i \
{ return (var ? [var newSupplementalKeysWithPrefix: s startingIndex: i] : nil); } \
-(NSArray *)newSupplementalValuesWithPrefix: (NSString *)s startingIndex: (int)i \
{ return (var ? [var newSupplementalValuesWithPrefix: s startingIndex: i] : nil); }


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface SCBaseProductFields : NSObject
{
    BOOL name;
    BOOL manufacturer;
    BOOL brand;
    BOOL sku;
    BOOL upc;
    BOOL mpn;
    BOOL retailerProductID;
    BOOL shortDescription;
    BOOL longDescription;
    BOOL parentGrpid;
    BOOL supplemental;
}

@property (readwrite) BOOL name;
@property (readwrite) BOOL manufacturer;
@property (readwrite) BOOL brand;
@property (readwrite) BOOL sku;
@property (readwrite) BOOL upc;
@property (readwrite) BOOL mpn;
@property (readwrite) BOOL retailerProductID;
@property (readwrite) BOOL shortDescription;
@property (readwrite) BOOL longDescription;
@property (readwrite) BOOL parentGrpid;
@property (readwrite) BOOL supplemental;

-(NSArray *)newArray;

@end


enum GPSSDKProductType
{
    GPSSDKProductTypeDefault,
    GPSSDKProductTypeOffer,
    GPSSDKProductTypeCoupon,
    GPSSDKProductTypeUniqueCoupon
};

enum GPSSDKProductType gpssdkProductType(id<SCBaseProduct> p);
