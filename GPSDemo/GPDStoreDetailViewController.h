//
//  GPDStoreDetailViewController.h
//  GPSDemo
//
//  Created by James Lee on 10/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDViewController.h"

@interface GPDStoreDetailViewController : GPDViewController

@property (strong, nonatomic) id<StoreData> store;

@end

@interface GPDStoreAnnotation : NSObject  <MKAnnotation>
@property (strong, nonatomic) id<StoreData> store;
@end
