//
//  SCDWShippingMethod.h
//  michaels
//
//  Created by James Lee on 7/19/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

@interface SCDWShippingMethod : NSObject

@property (nonatomic, strong) NSString *shipping_id;
@property (nonatomic, strong) NSString *description;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSDecimalNumber *price;

@property (nonatomic, strong) NSDictionary *customAttributes;

- (id)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)dictionaryObject;

@end


//@property (nonatomic, strong) NSString *c_omsShippingID; // michaels-specific