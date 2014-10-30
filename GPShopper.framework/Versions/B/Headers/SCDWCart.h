//
//  SCDWCart.h
//  Slifter+Demandware Cart
//
//  Created by James Lee on 5/13/14.
//  Copyright (c) 2014 GPShopper LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SCDWProduct.h"
#import "SCDWAddress.h"
#import "SCDWPaymentMethod.h"
#import "SCDWShippingMethod.h"
#import "SCDWProfile.h"
#import "SCDWCustomerInfo.h"
#import "SCCartWarning.h"
#import "InfoPacket.h"
//#import "SCDWCardPaymentInfo.h"
//#import "SCDWGiftCard.h"


#define kCartContentsUpdated @"kCartContentsUpdatedNotification"
#define kCartCheckoutInfoUpdated @"kCartCheckoutInfoUpdatedNotification" // Extension of kCartContentsUpdate - Cart gets updated whenever checkoutInfo is updated

#define kCartFetchFailed @"SCCartFetchFailedNotification"


@interface SCDWCart : NSObject <SCObjectRetrieverListener> {

}
// JJL: Debug Methods
@property (nonatomic, strong) NSObject *responseData;
// JJL: End Debug methods

@property (readonly, nonatomic) NSDecimalNumber *productTotal;
@property (readonly, nonatomic) NSDecimalNumber *productSubtotal;
@property (readonly, nonatomic) NSDecimalNumber *shippingTotal;
@property (readonly, nonatomic) NSDecimalNumber *taxTotal;
@property (readonly, nonatomic) NSDecimalNumber *orderTotal;

@property (readonly, nonatomic) NSInteger productCount;
@property (readonly, nonatomic) NSString *currency;

@property (readonly, nonatomic) NSArray *products;
@property (readonly, nonatomic) NSArray *warnings;

@property (readonly, nonatomic) NSArray *shippingMethods;
@property (readonly, nonatomic) NSArray *paymentMethods;
@property (readonly, nonatomic) NSArray *addresses;

@property (readonly, nonatomic) SCDWShippingMethod *selectedShippingMethod;
@property (readonly, nonatomic) SCDWPaymentMethod *selectedPaymentMethod;

@property (readonly, nonatomic) SCDWAddress *shippingAddress;
@property (readonly, nonatomic) SCDWAddress *billingAddress;
@property (readonly, nonatomic) SCDWCustomerInfo *customerInfo;

@property (readonly, nonatomic) NSString *error;

+(NSString *)requestUrl;
+(void)setRequestUrl: (NSString *)url;

+ (SCDWCart *)defaultCart;

- (void)fetch;
- (void)fetchThen:(void (^)(BOOL success))completion;

- (void)addProductID:(NSString *)productID quantity:(NSUInteger)quantity;
- (void)addProductID:(NSString *)productID quantity:(NSUInteger)quantity completion:(void (^)(BOOL success))completion;

- (void)removeItemAtIndex:(NSUInteger)index;
- (void)removeItemAtIndex:(NSUInteger)index completion:(void (^)(BOOL success))completion;

- (void)updateQuantity:(NSUInteger)quantity forIndex:(NSUInteger)index;
- (void)updateQuantity:(NSUInteger)quantity forIndex:(NSUInteger)index completion:(void (^)(BOOL success))completion;

@end


@interface SCDWCart (Checkout)

- (void)setBillingAddress:(SCDWAddress *)address;
- (void)setBillingAddress:(SCDWAddress *)address completion:(void (^)(BOOL success))completion;

- (void)setShippingAddress:(SCDWAddress *)address parameters:(NSDictionary *)parameters;
- (void)setShippingAddress:(SCDWAddress *)address parameters:(NSDictionary *)parameters completion:(void (^)(BOOL success))completion;

- (void)setCustomerInfo:(SCDWCustomerInfo *)customerInfo;
- (void)setCustomerInfo:(SCDWCustomerInfo *)customerInfo completion:(void (^)(BOOL success))completion;

- (void)setPaymentMethod:(NSString *)paymentID;
- (void)setPaymentMethod:(NSString *)paymentID completion:(void (^)(BOOL success))completion;

- (void)setShippingMethod:(NSString *)shippingID;
- (void)setShippingMethod:(NSString *)shippingID completion:(void (^)(BOOL success))completion;

- (void)fetchStatus;
- (void)fetchStatusThen:(void (^)(BOOL success))completion;

- (void)submit;
- (void)submitThen:(void (^)(BOOL success))completion;

- (void)fetchPaymentMethodsThen:(void (^)(BOOL success))completion;
- (void)fetchShippingMethodsThen:(void (^)(BOOL success))completion;

@end
