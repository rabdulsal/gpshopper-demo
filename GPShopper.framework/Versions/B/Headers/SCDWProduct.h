//
//  SCCartItem.h
//
//  Created by James Lee on 6/4/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "SCBaseProduct.h"

@interface SCDWProduct : SCBaseProduct

@property (nonatomic, readonly, strong) NSString *product_name;
@property (nonatomic, readonly, assign) NSInteger product_id;           // Typically a product's retailerproductid
@property (nonatomic, readonly, assign) NSInteger quantity;
@property (nonatomic, readonly, strong) NSString *item_text;

@property (nonatomic, readonly, strong) NSDecimalNumber *base_price;    // Unit price
@property (nonatomic, readonly, strong) NSDecimalNumber *price;         // Price * quantity
@property (nonatomic, readonly, strong) NSDecimalNumber *adjusted_price;// Checkout price for item

- (id)initWithDictionary:(NSDictionary *)dictionary;


@end
