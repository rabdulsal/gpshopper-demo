//
//  SearchResult.h
//  Slifter_iphone_rewrite
//
//  Created by kimberly on 3/12/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ProductInfo.h"
#import "SCDomain.h"

extern const int LOCATION_LOCAL;
extern const int LOCATION_ONLINE;

@class ImageCollection;
@class GenericFilterBucket;
@class SCCache;
 

enum SCSearchResultOrdering
{
    SCSearchResultOrderingDefault,
    SCSearchResultOrderingDistance
};

@interface SCSearchResultProduct : NSObject < SCBaseProduct, NSCoding >
{
    int originalRank;
    SCBaseProduct *productInfo;
    NSArray *productInstances;
}

@property (readonly) NSArray *productInstances;

-(id)initWithProductInfo: (SCBaseProduct *)p
               instances: (NSArray *)is;

-(InstanceSpecificInfo *)nearestPhysicalInstance;
-(InstanceSpecificInfo *)onlineInstance;
-(double)minDistance;

-(NSComparisonResult)distanceCompare: (SCSearchResultProduct *)p;
-(NSComparisonResult)localPriceAscCompare: (SCSearchResultProduct *)p;
-(NSComparisonResult)localPriceDescCompare: (SCSearchResultProduct *)p;
-(NSComparisonResult)onlinePriceAscCompare: (SCSearchResultProduct *)p;
-(NSComparisonResult)onlinePriceDescCompare: (SCSearchResultProduct *)p;
-(float)regularPriceFromSupplemental;
-(NSString *)salePriceRangeFromSupplemental;

-(uint64_t)regularPrice;
-(uint64_t)price;

@end

@interface SearchResultList : NSObject < NSCoding >
{	
	NSArray *grpids;
    NSArray *products;
	NSMutableDictionary *filtersByKey;
    NSDictionary *customFilters;

	int listType;
}

-(id)initWithGrpids: (NSArray *)gs
           products: (NSArray *)ps
      customFilters: (NSDictionary *)cfs;

-(id)initWithProducts: (NSArray *)ps
supplementalFilterMultiDomain: (id<SCMultiDomain>)md
    totalProductCount: (uint)r
      currentMaxIndex: (uint)i;

@property (nonatomic) int listType;
@property (readonly) NSArray *grpids;
@property (readonly) NSArray *products;
@property (readonly) uint totalProductCount;
@property (readonly) uint currentMaxIndex;
@property (readonly) NSMutableDictionary *filtersByKey;
@property (readonly) NSDictionary *customFilters;
@property (readonly) id<SCMultiDomain> supplementalFilterMultiDomain;

-(void)addFilterBucket: (GenericFilterBucket *)gfb
				   key: (NSString *)k;
-(NSDictionary *)newFiltersFromQuery: (NSString *)query;
-(NSArray *)newDistanceSortedGrpids;

-(NSArray *)productsOrderedBy: (int)o
                 includeLocal: (BOOL)il
                includeOnline: (BOOL)io;

+(NSString *)unconditionalQuery: (NSString *)query;

+(SearchResultList *)copyOfList: (SearchResultList *)l
               sortedBySelector: (SEL)s;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------

enum SearchImageSize
{
    SearchImageMedium=(1<<6),
    SearchImageLarge=(1<<7)
};

@interface SearchFeatures : NSObject
{
	BOOL upc;
	BOOL mpn;
	BOOL shortDesc;
	BOOL storeInfo;
	BOOL filters;
	BOOL manufacturer;
	BOOL regularPrice;
	BOOL hideSalePrice;
	BOOL dist;
	BOOL storeid;
    
    uint64_t imageSizes;
}

@property (readwrite) BOOL upc;
@property (readwrite) BOOL mpn;
@property (readwrite) BOOL shortDesc;
@property (readwrite) BOOL storeInfo;
@property (readwrite) BOOL filters;
@property (readwrite) BOOL manufacturer;
@property (readwrite) BOOL regularPrice;
@property (readwrite) BOOL hideSalePrice;
@property (readwrite) BOOL dist;
@property (readwrite) BOOL storeid;
@property (readwrite) uint64_t imageSizes;

-(uint64_t)flags;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SearchResultManager : NSObject
{}

+(void)setRequestUrl: (NSString *)url;
+(void)setDefaultZipcode: (NSString *)zip;
+(void)setDefaultRadius: (uint64_t)radius;
+(void)setMaxInstancesPerProduct: (uint64_t)n;
+(void)setSearchFeatures: (SearchFeatures *)features;

+(NSString *)aliasedQuery: (NSString *)query;
+(void)aliasQuery: (NSString *)query
			   as: (NSString *)alias;

+(SearchResultList *)searchForQuery: (NSString *)query;
+(SearchResultList *)searchForQuery: (NSString *)query
							zipcode: (NSString *)zipcode
							 radius: (uint64_t)radius;
+(void)clearSearches;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


enum SCSearchIterationType
{
    SCSearchIterationAutomatic,
    SCSearchIterationManual
};


/**
 Specifies batching of search results into 'pages'
 for ease of delivery and display.
 
 This class is one property of SCSearchSpecs,
 which is used by SCSearchFetcher.
 */
@interface SCSearchPagination : NSObject

/**
 Number of products per page.
 */
@property (readonly) uint64_t pageSize;

/**
 Indicates to the class managing this search request
 whether to continue fetching pages automatically
 or to wait for the next page to be requested explicitly.
 */
@property (readonly) enum SCSearchIterationType iterationType;

-(id)initWithPageSize: (uint64_t)s
        iterationType: (enum SCSearchIterationType)t;

+(SCSearchPagination *)newDefaultPagination;

+(uint64_t)defaultPageSize;
+(void)setDefaultPageSize: (uint64_t)s;

+(enum SCSearchIterationType)defaultIterationType;
+(void)setDefaultIterationType: (enum SCSearchIterationType)t;

@end


/**
 Encapsulates the size of a search result set.

 This class is one property of SCSearchSpecs,
 which is used by SCSearchFetcher.
 */
@interface SCSearchConstraint : NSObject

/**
 Radius of the search, in hundredths of a mile.
 */
@property (readonly) uint64_t radius;

/**
 Maximum number of products to return.
 */
@property (readonly) uint64_t maxResults;

/**
 Maximum number of instances per product.
 
 For example, if a radius is 10000 (100 miles)
 and maxResults is 5, even if 10 stores contain
 a particular product, only the first 5 will be returned.
 */
@property (readonly) uint64_t maxInstances;

@property (readonly) NSDictionary *supplementalFilters;

@property (readonly) NSDictionary *rangedFilters;

-(id)initWithRadius: (uint64_t)r
         maxResults: (uint64_t)mr
       maxInstances: (uint64_t)mi
supplementalFilters: (NSDictionary *)fs __attribute__((deprecated));

-(id)initWithRadius: (uint64_t)r
         maxResults: (uint64_t)mr
       maxInstances: (uint64_t)mi
supplementalFilters: (NSDictionary *)fs
      rangedFilters: (NSDictionary *)rfs;

-(BOOL)isEqualToSearchConstraint: (SCSearchConstraint *)c;

+(uint)defaultRadius;
+(void)setDefaultRadius: (uint64_t)r;

+(uint)defaultMaxResults;
+(void)setDefaultMaxResults: (uint64_t)r;

+(uint)defaultMaxInstances;
+(void)setDefaultMaxInstances: (uint64_t)i;

+(SCSearchConstraint *)newDefaultConstraint;

@end


/**
 Encapsulates the 'where' of product search.
 
 Location can be specifed as either a zipcode or a latlon.

 This class is one property of SCSearchSpecs,
 which is used by SCSearchFetcher.
 */
@interface SCSearchLocation : NSObject

/**
 Zipcode of location.  If nil, ignored in favor of lat and lon.
 */
@property (readonly) NSString *zipcode;

/**
 Latitude.
 */
@property (readonly) double lat;

/**
 Longitude.
 */
@property (readonly) double lon;

-(id)initWithZipcode: (NSString *)z;

-(id)initWithLat: (double)l0
             lon: (double)l1;

-(id)initWithLat:(double)l0
             lon:(double)l1
         zipcode:(NSString *)z;

+(SCSearchLocation *)onlineLocation;

@end


/**
 Encapsulates additional data which can be requested with search.
 */
@interface SCSearchExtras : NSObject

/**
 When specified in the request, filters for supplemental values
 will be generated for the keys specified.  Example: ["brand", "special_feature"]
 */
@property (readonly) NSArray *supplementalFilterKeys;

-(id)initWithSupplementalFilterKeys: (NSArray *)ks;

@end


/**
 Encapsulates all the details needed to specify a product search.
 */
@interface SCSearchSpecs : NSObject

/**
 What the search is for.  Examples: "hdtv" or "dress"
 */
@property (readonly) NSString *query;
@property (readonly) NSString *zipcode;
@property (readonly) uint64_t radius;
@property (readonly) double lat;
@property (readonly) double lon;

/**
 Where the search should be done.
 
 May be a physical location or the magic 'online' location.
 */
@property (readonly) SCSearchLocation *location;

/**
 How large the total result set should be.
 */
@property (readonly) SCSearchConstraint *constraint;

/**
 How the result set should be delivered:
 all at once or in more manageable pages.
 */
@property (readonly) SCSearchPagination *pagination;

/**
 What extra data to fetch in addition to products.
 */
@property (readonly) SCSearchExtras *extras;

/**
 Optional argument intended to trigger a new search
 for cached searches that are sufficiently old.
 */
@property (readwrite) int64_t maxAgeInCache;

-(id)initWithQuery: (NSString *)q
          location: (SCSearchLocation *)l
        constraint: (SCSearchConstraint *)c
        pagination: (SCSearchPagination *)p
            extras: (SCSearchExtras *)e;

-(id)initWithQuery: (NSString *)q
          location: (SCSearchLocation *)l
        constraint: (SCSearchConstraint *)c
        pagination: (SCSearchPagination *)p;

-(id)initWithQuery: (NSString *)q
           zipcode: (NSString *)z;

-(id)initWithQuery: (NSString *)q
          latitude: (double)l0
         longitude: (double)l1;

-(id)initWithQuery: (NSString *)q
           zipcode: (NSString *)z
        constraint: (SCSearchConstraint *)c;

-(id)initWithQuery: (NSString *)q
          latitude: (double)l0
         longitude: (double)l1
        constraint: (SCSearchConstraint *)c;

-(id)initWithQuery: (NSString *)q
		   zipcode: (NSString *)z
			radius: (uint64_t)r;

-(id)initWithQuery: (NSString *)q
          latitude: (double)l0
         longitude: (double)l1
            radius: (uint64_t)r;

-(BOOL)isEqualToSearchSpecs: (SCSearchSpecs *)s;

-(NSString *)newStringRepresentation;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@class SCSearchFetcher;

@protocol SCSearchFetcherListener

-(void)scSearchFetcher: (SCSearchFetcher *)fetcher
		   fetchedList: (SearchResultList *)list
			  forSpecs: (SCSearchSpecs *)specs;

-(void)scSearchFetcher: (SCSearchFetcher *)fetcher
 fetchedNoListForSpecs: (SCSearchSpecs *)specs;

@end


@interface SCSearchFetcher : NSObject
{
    SCObjectRetriever *retriever;
    SCCache *cache;
	id<SCSearchFetcherListener> listener;
    // request -> specs
    NSMutableDictionary *requestToSpecs;
}

@property (assign) id<SCSearchFetcherListener> listener;

/**
 This allows multiple SCSearchFetcher instances
 to refer to the same SCCache instance
 while using different time frames for refreshing data.
 
 For example, an in-store app may wish
 to preserve search data for 3 months,
 but attempt to refresh data older than one week.
 In this case, the share cache [SCSearchFetcher cache]
 would have a timeout of 3 months, but individual fetchers
 could be set to 1 week.
 */
@property (readwrite) double requiredRefreshAge;

-(void)fetchList: (SCSearchSpecs *)specs;

-(void)continueFetch: (SCSearchSpecs *)s;

-(BOOL)refreshRequiredForSpecs: (SCSearchSpecs *)s;

+(NSDictionary *)dictionaryFromLocation: (SCSearchLocation *)l;

+(NSDictionary *)dictionaryFromExtras: (SCSearchExtras *)e;

+(SCCache *)cache;
+(NSString *)cacheKeyForSpecs: (SCSearchSpecs *)s;
+(SearchResultList *)cachedListForSpecs:(SCSearchSpecs *)s;
+(void)setRequestUrl: (NSString *)url;
+(void)setImageSizes: (NSArray *)ss;
+(void)setBaseProductFields: (NSArray *)fs;
+(void)enableMockDataWithFile: (NSString *)fn;

+(NSDictionary *)requestForSpecs: (SCSearchSpecs *)s;
-(SCSearchSpecs *)specsForRequest: (NSDictionary *)d;
-(NSDictionary *)responseForRequest: (NSDictionary *)d;
-(NSArray *)productsFromResponse: (NSDictionary *)d;
-(id<SCMultiDomain>)newSupplementalFilterMultiDomainFromSpecs: (SCSearchSpecs *)s
                                                     response: (NSDictionary *)rp;
-(void)fetchPageForSpecs: (SCSearchSpecs *)s;

@end


#define SCSEARCHFETCHER_ENSURE_EXISTS(sf, lstnr) \
if (!sf) { sf=[[SCSearchFetcher alloc] init]; [sf setListener: lstnr]; }
