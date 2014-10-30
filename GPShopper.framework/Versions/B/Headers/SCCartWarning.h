//
//  SCCartWarnings.h
//  michaels
//
//  Created by James Lee on 6/11/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    CustomerEmailRequired,
    BillingAddressRequired,
    PaymentMethodRequired,
    ShippingMethodRequired,
    ShippingAddressRequired,
    SCCartWarningTypeUnknown
} SCCartWarningType;

@interface SCCartWarning : NSObject


@property (nonatomic, assign) SCCartWarningType warningType;
- (id)initWithType:(SCCartWarningType)warningType;
- (NSString *)localizedMessage;
+ (SCCartWarningType)warningTypeForResponse:(NSString *)response;
@end
