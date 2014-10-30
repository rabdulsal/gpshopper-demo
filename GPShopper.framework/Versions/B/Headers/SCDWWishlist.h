//
//  SCDWWishlist.h
//  michaels
//
//  Created by James Lee on 7/25/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SCDWRetriever.h"
#import "SCDWWishlistItem.h"
#import "SCNullHandling.h"

@interface SCDWWishlist : NSObject

@property (strong, nonatomic) NSArray *items;
@property (strong, nonatomic) NSString *description;
@property (strong, nonatomic) NSString *name;

- (void)fetchThen:(SCDWResponseBlock)completion;
- (void)addProductID:(NSString *)productID completion:(SCDWResponseBlock)completion;
- (NSObject *)addProductIDSynchronously:(NSString *)productID error:(NSError **)error;
- (void)removeItem:(SCDWWishlistItem *)item completion:(SCDWResponseBlock)completion;

- (BOOL)containsProductWithID:(NSString *)product_id;
@end
