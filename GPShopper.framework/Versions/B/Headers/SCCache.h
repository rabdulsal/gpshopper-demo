//
//  SCCache.h
//  bestbuy
//
//  Created by kimberly on 3/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SCCACHE_M
#define SCCACHE_M

#import <Foundation/Foundation.h>


enum SCCacheDiskRecordFormat
{
    SCCacheDiskRecordFormatPlain=0,
    SCCacheDiskRecordFormatZlibCompressed=1
};


@interface SCCacheDiskRecord : NSObject < NSCoding >

@property (readonly) NSString *filename;
@property (readonly) double timestamp;
@property (readonly) enum SCCacheDiskRecordFormat format;

-(id)initWithFilename: (NSString *)fn
            timestamp: (double)t;

-(id)initWithFilename: (NSString *)fn
            timestamp: (double)t
               format: (enum SCCacheDiskRecordFormat)f;

@end


@interface SCCacheRecord : NSObject < NSCoding >

@property (readonly) NSObject *object;
@property (readonly) double timestamp;

-(id)initWithObject: (NSObject *)o
          timestamp: (double)t;

@end


/**
 A container that stores values by key (like a dictionary)
 and which times out values after a certain time.
 */
@protocol SCCache < NSObject >

/**
 Stores an object in the cache.
 
 The object will remain in the cache until its lifetime exceeds timeout.
 */
-(void)setObject: (NSObject *)obj
          forKey: (NSString *)key;

/**
 Removes object from cache.
 */
-(void)removeObjectForKey: (NSString *)key;

/**
 Returns the value for a given key, if it exists.
 */
-(NSObject *)objectForKey: (NSString *)k;

/**
 All keys currently stored in the cache.
 */
-(NSArray *)allKeys;

/**
 Clears the cache.
 */
-(void)removeAllObjects;

/**
 The time at which a given key was added to the cache.
 
 Assumed to be CFAbsoluteTimeGetCurrent(), which begins from 1/1/2001.
 */
-(double)timestampForKey: (NSString *)k;

/**
 The lifetime of each value in the cache, in seconds.
 */
-(double)timeout;

/**
 Sets the timeout for the cache.
 */
-(void)setTimeout: (double)t;

/**
 The maximum number of elements in this cache.
 */
-(uint64_t)maxCount;

/**
 Sets the maximum number of elements in this cache.
 */
-(void)setMaxCount: (uint64_t)s;

@end

extern const uint64_t scCacheMaxCount;


/**
 An implementation of SCCache that stores values in the device's filesystem.
 
 The files written are:
 
 * *filePrefix*_index = index of keys and timestamps
 * *filePrefix*_*hash of key* = an individual value
 */
@interface SCDiskOnlyCache : NSObject < SCCache >
{
    NSMutableDictionary *fileIndex;
    NSFileManager *fileManager;
}

@property (readwrite) double timeout;
@property (readwrite) uint64_t maxCount;

/**
 The prefix for all files written by this cache.
 */
@property (readonly) NSString *filePrefix;


@property (readwrite) enum SCCacheDiskRecordFormat recordFormat;

/**
 Designated initializer.
 
 @param n filePrefix
 
 @param t timeout
 */
-(id)initWithFilePrefix: (NSString *)n
                timeout: (double)t;

@end


@interface SCInMemoryCache : NSObject < SCCache >
{
    NSMutableDictionary *contents;
}

@property (readwrite) double timeout;
@property (readwrite) uint64_t maxCount;

-(id)initWithTimeout: (double)t;

@end


/**
 The 'standard' implementation of the SCCache protocol.
 
 Values are stored in memory and optionally on disk.
 */
@interface SCCache : NSObject < SCCache >
{
    SCDiskOnlyCache *diskOnlyCache;
    SCInMemoryCache *inMemoryCache;
}

@property (readwrite) double timeout;
@property (readwrite) uint64_t maxCount;

@property (readonly) SCDiskOnlyCache *diskOnlyCache;
@property (readonly) SCInMemoryCache *inMemoryCache;

-(id)initWithName: (NSString *)n
          timeout: (double)t;

-(void)setFilePrefix: (NSString *)s
    diskRecordFormat: (enum SCCacheDiskRecordFormat)f
     maxSizeInMemory: (int64_t)m;

-(NSString *)filePrefix;

-(enum SCCacheDiskRecordFormat)diskRecordFormat;

@end

#endif
