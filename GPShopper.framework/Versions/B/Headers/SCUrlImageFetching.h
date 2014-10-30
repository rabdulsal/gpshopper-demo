//
//  SCUrlImageFetching.h
//  project
//
//  Created by kimberly on 10/20/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef SCURLIMAGEFETCHING_H
#define SCURLIMAGEFETCHING_H

#import <Foundation/Foundation.h>

@class SCUrlImageFetcher;


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@protocol SCUrlImageFetcherListener

-(void)scUrlImageFetcher: (SCUrlImageFetcher *)fetcher
				gotImage: (UIImage *)image
				  forUrl: (NSString *)url;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCUrlImageFetcher : NSObject
{
	NSMutableSet *urls;
    NSMutableSet *requestedUrls;
	id<SCUrlImageFetcherListener> listener;
}

@property (assign) id<SCUrlImageFetcherListener> listener;


-(id)initWithListener: (id<SCUrlImageFetcherListener>)l;
-(UIImage *)imageForUrl: (NSString *)url;
-(UIImage *)imageForUrl: (NSString *)url context:(NSString *)imageContext;
-(UIImage *)imageForUrl:(NSString *)url context:(NSString *)imageContext storageTargets: (NSUInteger)t;
-(void)decache;

@end




//--------------------------------------------------------------------
//--------------------------------------------------------------------


enum SCUrlImageStorage
{
    SCUrlImageStorageInMemory = (1 << 0),
    SCUrlImageStorageOnDisk   = (1 << 1)
};

@interface SCUrlImageSpec : NSObject

@property (readonly) NSString *url;
@property (readonly) NSString *context;
@property (readonly) NSUInteger storageLocations;

-(id)initWithUrl: (NSString *)u
         context: (NSString *)c
storageLocations: (NSUInteger)s;

@end


@interface SCUrlImageQueueingModel : NSObject
{
    NSMutableArray *stack;
    NSMutableDictionary *contexts;
}

-(void)addSpec: (SCUrlImageSpec *)s;
-(SCUrlImageSpec *)nextSpec;
-(void)removeSpec;
-(NSUInteger)count;

@end


@interface UrlImageCache : NSObject

+(void)setUrlPrefix: (NSString *)prefix;
+(void)setNumCacheDays: (uint64_t)ncd;
+(NSString *)newUrlForHash: (NSData *)hash;
+(NSString *)newUrlForHashStr: (NSString *)hash;
+(UIImage *)imageForUrl: (NSString *)url
				   wait: (BOOL)wait;
+(UIImage *)imageForHashStr: (NSString *)hash
					   wait: (BOOL)wait;


+(UIImage *)localImageForHashStr: (NSString *)hash;
+(void)cacheUrl: (NSString *)url;
+(void)printHistoryToLog;

+(UIImage *)imageForUrl:(NSString *)url 
                context:(NSString *)imageContext
                   wait: (BOOL)wait;

+(UIImage *)imageForUrl: (NSString *)u
                context: (NSString *)c
         storageTargets: (NSUInteger)t;

+(void)removeImageForUrl: (NSString *)url;
    

@end

#endif
