//
//  ProductInfo.h
//  Slifter_iphone_rewrite
//
//  Created by kimberly on 1/18/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "Utils.h"
#import "InfoPacket.h"
#import "SCBaseProduct.h"
#import "SCMacros.h"
#import "SCCache.h"

@class ImageCollection;
@class ImageRecord;


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface PositionAttribute : NSObject
{
	uint64_t zone;
	uint64_t position;
	NSString *name;
	NSString *value;
}

@property (nonatomic) uint64_t zone;
@property (nonatomic) uint64_t position;
@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *value;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@protocol ProductInfo < SCBaseProduct >

-(NSString *)searchImageUrl;
-(uint64_t)regularPrice;
-(uint64_t)price;

@end


@protocol SCProductInfoSupplementalConstructor

-(NSObject *)newSupplementalObjectForAttrs: (NSDictionary *)as;

@end


@interface ProductInfo : SCBaseProduct < ProductInfo >

-(id)initWithBaseProduct: (SCBaseProduct *)b;
-(id)initWithProductInfo: (ProductInfo *)p;

-(NSString *)searchImageUrl;
-(uint64_t)minDistance;
-(uint64_t)price;

+(BOOL)grpidIsGood: (uint64_t)grpid;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


/**
 All the information associated with a store.
 
 Corresponds to table gpshopper_1_1.Store in the database.
 */
@protocol StoreData < NSObject >

/** @name Store name */

/**
 The name of the store.  Often the franchise name (ex. 'Best Buy')
 */
-(NSString *)storeName;

/**
 The name of the particular store location (ex. 'Soho' or 'Best Buy Soho')
 */
-(NSString *)storeSubname;

/** @name Location */

/**
 Street address (ex. '123 Main St.')
 */
-(NSString *)streetAddress;

/** City name (ex. 'Springfield') */
-(NSString *)city;

/** State (ex. 'IL') */
-(NSString *)state;

/**
 A nicely formatted string containing city and state (and zipcode?).
 
 @warning DEPRECATED.  Use city and state instead.
 */
-(NSString *)cityState;

/**
 Zipcode.
 
 In addition to real zipcodes, can also take on a few 'magic' values:
 
     - 'online':  This is the online store.
     - 'gta':  This is the global-to-all store.
 */
-(NSString *)zipcode;

/** Latitude. */
-(double)lat;

/** Longitude. */
-(double)lng;

/**
 CLLocation instance for accessing CoreLocation functionality (primarily distance).
 */
-(CLLocation *)cllocation;

/** @name Additional information */

/** Phone number (ex. '1234567890') */
-(NSString *)phone;

/** Hours (ex. 'Mon-Fri 10am-8pm') */
-(NSString *)hours;

/** Url of a map at the store location. */
-(NSString *)mapUrl;

/** Promotional message. */
-(NSString *)storeMessage;

/**
 Retailer id.
 
 Corresponds to key on table gpshopper_1_1.Retailer.
 */
-(uint16_t)retailerid;

-(uint64_t)storeid;

/**
 The retailer's own identifier for a store,
 as opposed to GPShopper's internal identifier.
 */
-(NSString *)storeExternalID;

/** Supplemental key-value pairs */
-(NSDictionary *)storeSupplemental;

@end

#define FORWARD_STORE_DATA_IMPL(var) \
FORWARD_SELECTOR(var, storeName, NSString *, nil) \
FORWARD_SELECTOR(var, storeSubname, NSString *, nil) \
FORWARD_SELECTOR(var, streetAddress, NSString *, nil) \
FORWARD_SELECTOR(var, city, NSString *, nil) \
FORWARD_SELECTOR(var, state, NSString *, nil) \
FORWARD_SELECTOR(var, cityState, NSString *, nil) \
FORWARD_SELECTOR(var, phone, NSString *, nil) \
FORWARD_SELECTOR(var, hours, NSString *, nil) \
FORWARD_SELECTOR(var, lat, double,  -1.0) \
FORWARD_SELECTOR(var, lng, double, -1.0) \
FORWARD_SELECTOR(var, cllocation, CLLocation *, nil) \
FORWARD_SELECTOR(var, mapUrl, NSString *, nil) \
FORWARD_SELECTOR(var, zipcode, NSString *, nil) \
FORWARD_SELECTOR(var, storeMessage, NSString *, nil) \
FORWARD_SELECTOR(var, retailerid, uint16_t, 0) \
FORWARD_SELECTOR(var, storeid, uint64_t, 0) \
FORWARD_SELECTOR(var, storeExternalID, NSString*, nil) \
FORWARD_SELECTOR(var, storeSupplemental, NSDictionary *, nil)

@interface NSString ( StoreData )

-(NSString *)stringByReplacingPropertiesFromStoreData: (id<StoreData>)s;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@protocol ProductInstance < NSObject >

-(uint64_t)piid;
-(uint64_t)price;
-(uint64_t)salePrice;
-(uint64_t)distance;
-(NSString *)inStockMessage;
-(NSString *)instanceUrl;
-(NSString *)promo;
-(uint64_t)availability;
-(NSDate *)startDate;
-(NSDate *)stopDate;

@end


enum InstanceOrdering
{
	InstanceOrderingDistance,
	InstanceOrderingPrice,
	InstanceOrderingName
};


//----------------------------------------------------------------
//----------------------------------------------------------------


@class StoreData;

@interface InstanceSpecificInfo : NSObject < ProductInstance, StoreData, NSCoding >
{
	// Per instance.
	uint64_t piid;
	uint64_t grpid;
	uint64_t availability;
	uint64_t price;
	uint64_t salePrice;
	BOOL hideSalePrice;
	NSUInteger store;
	NSUInteger retailer;
	uint64_t distance;
	NSString *stock;
	NSString *promoType;
	NSString *promo;
	NSString *marketingMessage;
	NSMutableArray *alternateStores;
	NSString *retailerName;
	NSString *productUrl;
    StoreData *storeData;
}

@property (nonatomic) uint64_t grpid;
@property (nonatomic) uint64_t salePrice;
@property (nonatomic) BOOL hideSalePrice;
@property (nonatomic) NSUInteger store;
@property (nonatomic) NSUInteger retailer;
@property (nonatomic, retain) NSString *promoType;
@property (nonatomic, retain) NSString *promo;
@property (nonatomic, retain) NSString *stock;
@property (nonatomic, retain) NSString *marketingMessage;
@property (nonatomic, retain) NSMutableArray *alternateStores;
@property (nonatomic, retain) NSString *retailerName;
@property (nonatomic, retain) NSString *productUrl;
@property (nonatomic, retain) NSDate *startDate;
@property (nonatomic, retain) NSDate *stopDate;
@property (retain) StoreData *storeData;

-(id)initWithPiid: (uint64_t)i;

-(id)initWithPiid: (uint64_t)p0
            price: (uint64_t)p1
         distance: (uint64_t)d
          storeid: (uint64_t)s
   inStockMessage: (NSString *)m
              url: (NSString *)u
     availability: (uint64_t)a;

-(uint64_t)lowestPrice;

-(BOOL)matchesRetailer: (NSString *)ret;
-(BOOL)matchesLocation: (int)loc;

-(void)updateWithDictionary: (NSDictionary *)d;

+(InstanceSpecificInfo *)newFromDictionary: (NSDictionary *)d;

@end


#define FORWARD_PRODUCT_INSTANCE_IMPL(var) \
FORWARD_SELECTOR(var, piid, uint64_t, 0) \
FORWARD_SELECTOR(var, price, uint64_t, 0) \
FORWARD_SELECTOR(var, salePrice, uint64_t, 0) \
FORWARD_SELECTOR(var, distance, uint64_t, 0) \
FORWARD_SELECTOR(var, inStockMessage, NSString *, nil) \
FORWARD_SELECTOR(var, instanceUrl, NSString *, nil) \
FORWARD_SELECTOR(var, promo, NSString *, nil) \
FORWARD_SELECTOR(var, availability, uint64_t, 0)


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface StoreData : NSObject < StoreData, NSCoding >
{
	uint64_t storeid;
	NSString *name;
    NSString *subName;
	NSString *superName;
	uint16_t retailerid;
	NSString *streetAddress;
    NSString *city;
    NSString *state;
	NSString *cityState;
	NSString *phone;
	NSString *hours;
    NSString *fax;
    NSString *message;
    NSString *extType;
	double lat;
	double lng;
	UIImage *map;
	double encodeTimestamp;
	NSString *md5;
    NSString *mapUrl;
    NSString *zipcode;
    NSString *externalID;
    NSDictionary *storeSupplemental;
}

@property (copy) NSString *name;
@property (copy) NSString *superName;
@property (copy) NSString *fax;
@property (copy) NSString *extType;
@property (nonatomic, retain) UIImage *map;
@property (nonatomic, readonly) double encodeTimestamp;
@property (copy) NSString *md5;
@property (readonly) CLLocation *cllocation;

-(id)initWithStoreid: (uint64_t)i
          retailerid: (uint16_t)r
           storeName: (NSString *)n
             subName: (NSString *)sn
       streetAddress: (NSString *)sa
                city: (NSString *)c
               state: (NSString *)s
               phone: (NSString *)p
               hours: (NSString *)h
            latitude: (double)l0
           longitude: (double)l1
             zipcode: (NSString *)z
             message: (NSString *)m1
          externalID: (NSString *)ei
        supplemental: (NSDictionary *)kv;

-(id)initWithStoreid: (uint64_t)i
          retailerid: (uint16_t)r
           storeName: (NSString *)n
             subName: (NSString *)sn
       streetAddress: (NSString *)sa
                city: (NSString *)c
               state: (NSString *)s
               phone: (NSString *)p
               hours: (NSString *)h
            latitude: (double)l0
           longitude: (double)l1
              mapUrl: (NSString *)m0
             zipcode: (NSString *)z
             message: (NSString *)m1
        supplemental: (NSDictionary *)kv __attribute__((deprecated));

-(void)updateWithDictionary: (NSDictionary *)d;

+(StoreData *)newFromDictionary: (NSDictionary *)d;

+(NSArray *)allStoreFields;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@class SCStoresFetcher;
@class SCCache;

@protocol SCStoresFetcherListener <NSObject>

-(void)scStoresFetcher: (SCStoresFetcher *)f
         fetchedStores: (NSArray *)ss
         forRetailerId: (uint64_t)r;

-(void)scStoresFetcher: (SCStoresFetcher *)f
fetchedNoStoresForRetailerId: (uint64_t)r;

@end

@interface SCStoresFetcher : NSObject
{
    SCObjectRetriever *retriever;
}

@property (assign) id<SCStoresFetcherListener> listener;

-(void)fetchStoresForRetailerId: (uint64_t)r;

+(SCCache *)defaultCache;
+(void)setRequestUrl: (NSString *)s;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface AlternateStore : NSObject
{
	uint64_t storeid;
	uint64_t grpid;
	uint64_t piid;
	NSString *name;
	NSUInteger dist;
}

@property (nonatomic) uint64_t storeid;
@property (nonatomic) uint64_t grpid;
@property (nonatomic) uint64_t piid;
@property (nonatomic, retain) NSString *name;
@property (nonatomic) NSUInteger dist;

-(NSComparisonResult)distanceCompare: (AlternateStore *)element;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface SCLocalizedProduct : NSObject < SCBaseProduct, ProductInstance, StoreData, NSCoding >
{
    SCBaseProduct *product;
    InstanceSpecificInfo *instance;
    NSArray *children;
    NSArray *nearbyInstances;
}

@property (readonly) NSArray *children;
@property (readonly) NSArray *nearbyInstances;

-(id)initWithProduct: (SCBaseProduct *)p
            instance: (InstanceSpecificInfo *)i
            children: (NSArray *)cs
     nearbyInstances: (NSArray *)ns;

-(NSArray *)newChildrenWhereSupplementalForKey: (NSString *)k
                                        equals: (NSString *)v;

-(NSArray *)newChildrenMatchingSupplementalValues: (NSDictionary *)s;

-(NSArray *)newChildSupplementalValuesForKey: (NSString *)k;

-(uint64_t)salePrice;
-(NSString *)marketingMessage;

//-(double)minPrice;
//-(double)maxPrice;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@class SCLocalizedProductFetcher;

@protocol SCLocalizedProductFetcherListener

-(void)scLocalizedProductFetcher: (SCLocalizedProductFetcher *)f
                  fetchedProduct: (SCLocalizedProduct *)p;

-(void)scLocalizedProductFetcherFailed: (SCLocalizedProductFetcher *)f;

@end


#define kSCLocalizedProductSpecsLookupStrategyLocal @"local"
#define kSCLocalizedProductSpecsLookupStrategyOnline @"online"

@interface SCLocalizedProductSpecs : NSObject

@property (readonly) uint64_t grpid;
@property (readonly) uint64_t piid;
@property (readonly) NSString *zipcode;
@property (readonly) NSString *lookupStrategy;
@property (readonly) int64_t maxAgeInCache;

-(id)initWithGrpid: (uint64_t)g
              piid: (uint64_t)p
           zipcode: (NSString *)z
    lookupStrategy: (NSString *)l
     maxAgeInCache: (int64_t)a;

+(SCLocalizedProductSpecs *)newSpecsForGrpid: (uint64_t)g
                                        piid: (uint64_t)p
                                     zipcode: (NSString *)z;

@end


@interface SCLocalizedProductFetcher : NSObject
{
    NSString *lookupStrategy;
    SCObjectRetriever *retriever;
    int hitContext;
    id<SCLocalizedProductFetcherListener> listener;
}

@property (copy) NSString *lookupStrategy;
@property (assign) id<SCLocalizedProductFetcherListener> listener;
@property (readwrite) int hitContext;

-(id)initWithListener: (id<SCLocalizedProductFetcherListener>)l;
-(void)fetchLocalizedProductForGrpid: (uint64_t)g
                             zipcode: (NSString *)z;
-(void)fetchLocalizedProductForGrpid: (uint64_t)g
                                piid: (uint64_t)p
                             zipcode: (NSString *)z;
-(void)fetchLocalizedProductForSpecs: (SCLocalizedProductSpecs *)p;
+(void)setRequestUrl: (NSString *)s;
+(NSString *)requestUrl;
+(void)setImageSizes: (NSArray *)ss;

/**
 The maximum radius for nearby instances.
 
 Hundredths of a mile.
 */
+(void)setMaxDistance: (uint64_t)h;

+(SCCache *)cache;

@end


@interface SCLocalizedProductResponseParser : SCRemoteResponseParser
{}

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface ProductInfoFeatures : NSObject
{
	BOOL requestLargeImage;
}

@property (readwrite) BOOL requestLargeImage;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface ProductInfoManager : NSObject
{
	NSMutableDictionary *retailerListCache;
}

+(void)setRequestUrl: (NSString *)url;
+(void)setDefaultZipcode: (NSString *)zip;
+(void)setFeatures: (ProductInfoFeatures *)pif;

+(void)setStoreData: (StoreData *)sd
         forStoreId: (uint64_t)i;

+(StoreData *)storeDataForStoreId: (uint64_t)i;

+(StoreData *)storeDataForKey: (uint64_t)store
                       create: (BOOL)create;

+(StoreData *) storeData: (uint64_t)piid;

+(InstanceSpecificInfo *) instanceSpecificInfo: (uint64_t)piid
										create: (BOOL)create;
+(void)setInstanceSpecificInfo: (InstanceSpecificInfo *)i
                       forPiid: (uint64_t)p;
 
+(ProductInfo *) productInfoForKey: (uint64_t)grpid
							create: (BOOL)create;
+(ProductInfo *)productInfoForGrpid: (uint64_t)grpid;

+(void)setProductInfo: (ProductInfo *)p
             forGrpid: (uint64_t)g;

+(uint64_t)closestPhysicalInstance: (uint64_t)grpid
						atRetailer: (NSString *)retailer;

+(uint64_t)cheapestInstance: (uint64_t)grpid;

-(NSSet *)retailersForGrpid: (uint64_t)grpid;

-(unsigned int)numRetailersForGrpid: (uint64_t)grpid;

+(uint64_t)bestInstance: (uint64_t)grpid
			   ordering: (int)ordering
			   retailer: (NSString *)retailer
			   location: (int)location;

+(void)requestProductInfoWithGrpid: (uint64_t)grpid
							  piid: (uint64_t)piid
						   zipcode: (NSString *)zipcode
						hitContext: (uint64_t)hitContext;

+(void)requestProductInfoWithGrpid: (uint64_t)grpid
							  piid: (uint64_t)piid
						hitContext: (uint64_t)hitContext;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface SCProductImageSpecs : NSObject
{
	uint64_t grpid;
	uint64_t width;
	uint64_t height;
}

@property (readonly) uint64_t grpid;
@property (readonly) uint64_t width;
@property (readonly) uint64_t height;

-(id)initWithGrpid: (uint64_t)g
			 width: (uint64_t)w
			height: (uint64_t)h;

@end

//----------------------------------------------------------------
//----------------------------------------------------------------


@interface SCProductImageRetriever : SCObjectRetriever
{
//	SCRemoteRequester *requester;
//	SCRequestConstructor *requestConstructor;
}

-(id)initWithRequester: (SCRemoteRequester *)rr
	requestConstructor: (SCRequestConstructor *)rc;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


// notification: lp_data_changed
@interface SCLandingPageData : NSObject
{
	uint64_t grpid;
	uint64_t piid;
	
	ProductInfo *product;
	InstanceSpecificInfo *instance;
	StoreData *store;
    
    BOOL updatedFromRemote;
}

-(id)initWithGrpid: (uint64_t)g
			  piid: (uint64_t)p;

-(void)fetchData;

@property (readonly) uint64_t grpid;
@property (readonly) uint64_t piid;
@property (readonly) ProductInfo *product;
@property (readonly) InstanceSpecificInfo *instance;
@property (readonly) StoreData *store;
@property (readonly) BOOL updatedFromRemote;

-(NSDictionary *)dataAttrs;
-(NSObject *)supplemental;

@end
