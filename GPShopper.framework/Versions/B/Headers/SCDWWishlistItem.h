//
//  SCDWWishlistItem.h
//  michaels
//
//  Created by James Lee on 8/1/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SCBaseProduct.h"

@interface SCDWWishlistItem : NSObject  <SCBaseProduct>

@property (strong, nonatomic) NSString *wishlist_id;

- (id)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)dictionaryObject;
@end
