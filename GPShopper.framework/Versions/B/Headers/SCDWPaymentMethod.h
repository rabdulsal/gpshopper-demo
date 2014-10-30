//
//  SCDWPaymentMethod.h
//  michaels
//
//  Created by James Lee on 7/19/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

@interface SCDWPaymentMethod : NSObject

@property (nonatomic, strong) NSString *payment_id;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *image;
@property (nonatomic, strong) NSString *description;
@property (nonatomic, strong) NSArray *cards;

@property (nonatomic, strong) NSArray *customAttributes;

- (id)initWithDictionary:(NSDictionary*)dictionary;
- (NSDictionary *)dictionaryObject;

@end


@interface SCDWPaymentCard : SCDWPaymentMethod

@property (nonatomic, strong) NSString *card_type;

- (id)initWithDictionary:(NSDictionary*)dictionary;
- (NSDictionary *)dictionaryObject;

@end
