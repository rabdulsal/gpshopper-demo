//
//  GPDImageFetcher.m
//  GPSDemo
//
//  Created by James Lee on 10/9/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDImageFetcher.h"



static NSCache *sharedImageCache;
static GPDImageFetcher *sharedInstance;

@interface GPDImageFetcher ()
@property (strong, nonatomic) NSMutableDictionary *downloadsInProgress;
@end

@implementation GPDImageFetcher

- (instancetype)init
{
    self = [super init];
    if (self) {
        _downloadsInProgress = [NSMutableDictionary dictionary];
    }
    return self;
}

- (UIImage *)cachedImageForURL:(NSString *)url
{
    return [sharedImageCache objectForKey:url];
}

- (void)fetchImageForURL:(NSString *)url cache:(BOOL)cache completion:(void (^)(UIImage *))completion
{
//    NSAssert(!_downloadsInProgress[url], @"should handle multiple downloads");
    
    if (url.length) {
        NSURLRequest *request = [[NSURLRequest alloc] initWithURL:[NSURL URLWithString:url]
                                                      cachePolicy:NSURLRequestReturnCacheDataElseLoad
                                                  timeoutInterval:15.0];
        
        id handler = ^(NSURLResponse *response, NSData *data, NSError *connectionError) {
            
            UIImage *image = nil;
            if (data && data.length > 512) {
                image = [UIImage imageWithData:data];
            }
            if (cache && image) {
                [sharedImageCache setObject:image forKey:url];
            }
            if (completion) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    completion(image);
                });
            }
            [_downloadsInProgress removeObjectForKey:url];
        };
        
        if (!_downloadsInProgress[url]) {
            [_downloadsInProgress setObject:@YES forKey:url];
            [NSURLConnection
             sendAsynchronousRequest:request
             queue:[NSOperationQueue mainQueue]
             completionHandler:handler];
        }
    }
}

+ (void)initialize
{
    sharedInstance = [GPDImageFetcher new];
    sharedImageCache = [[NSCache alloc] init];
    sharedImageCache.countLimit = 256;
}

+ (instancetype)sharedInstance
{
    return sharedInstance;
}

@end
