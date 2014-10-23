//
//  GPDImageFetcher.h
//  GPSDemo
//
//  Created by James Lee on 10/9/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GPDImageFetcher : NSObject

- (UIImage *)cachedImageForURL:(NSString *)url;

- (void)fetchImageForURL:(NSString *)url cache:(BOOL)cache completion:(void (^)(UIImage *image))completion;

+ (instancetype)sharedInstance;

@end
